// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "FbxParser.h"

#include <fbxsdk.h>
#include <filesystem>
#include "Engine.h"
#include "Materials/Material.h"
#include "Logging/LogMacros.h"
#include "DirectX/DirectXDeviceBundle.h"
#include "DirectX/DirectXCommon.h"
#include "SceneRendering/StaticMesh.h"
#include "COM/COMImageLoader.h"
#include "COM/COMBitmapFrame.h"

using namespace std;
using namespace std::filesystem;

FbxParser::FbxParser(Engine* engine, fbxsdk::FbxManager* fbxMgr) : Super()
	, engine(engine)
	, manager(fbxMgr)
	, importer(nullptr)
	, scene(nullptr)
{
	importer = fbxsdk::FbxImporter::Create(fbxMgr, "");
	if (importer == nullptr)
	{
		SE_LOG(LogAssets, Error, L"Cannot create fbx importer.");
		return;
	}
}

FbxParser::~FbxParser()
{
	if (importer != nullptr)
	{
		importer->Destroy(true);
		importer = nullptr;
	}
}

bool FbxParser::TryParse(TRefPtr<String> filepath)
{
	if (importer == nullptr)
	{
		SE_LOG(LogAssets, Error, L"Importer is not ready.");
		return false;
	}

	if (!importer->Initialize(filepath->AsMultiByte().c_str()))
	{
		SE_LOG(LogAssets, Error, L"Cannot initialize fbx file: {0}.", filepath);
		return false;
	}

	scene = fbxsdk::FbxScene::Create(manager, "FbxScene");
	if (scene == nullptr)
	{
		SE_LOG(LogAssets, Error, L"Cannot create fbx scene with file: {0}.", filepath);
		return false;
	}

	if (!importer->Import(scene, false))
	{
		SE_LOG(LogAssets, Error, L"Cannot import scene documents with file: {0}.", filepath);
		return false;
	}

	// Convert scene unit to meter.
	fbxsdk::FbxSystemUnit::m.ConvertScene(scene);
	// Convert scene axis to DirectX Axis.
	fbxsdk::FbxAxisSystem directX(fbxsdk::FbxAxisSystem::eYAxis, fbxsdk::FbxAxisSystem::eParityEven, fbxsdk::FbxAxisSystem::eRightHanded);
	directX.ConvertScene(scene);
	// Triangulate all scene items.
	fbxsdk::FbxGeometryConverter geometryConverter(manager);
	geometryConverter.Triangulate(scene, true);

	parentPath = path(filepath->C_Str).parent_path();
	if (!ProcessMaterials())
	{
		SE_LOG(LogAssets, Error, L"Cannot process materials from scene with file: {0}.", filepath);
		return false;
	}

	// Is STATIC MESH
	if (!ProcessStaticMeshes() || !ComposeStaticMeshes())
	{
		SE_LOG(LogAssets, Error, L"Cannot process static meshes from scene with file: {0}.", filepath);
		return false;
	}

	return true;
}

bool FbxParser::IsStaticMesh() const
{
	return staticMesh.IsValid;
}

TRefPtr<StaticMesh> FbxParser::GetStaticMesh() const
{
	return staticMesh;
}

bool FbxParser::ProcessMaterials()
{
	int32 numMaterials = scene->GetMaterialCount();
	materials.reserve(numMaterials);

	static auto GetFactorVector = [](fbxsdk::FbxDouble3 vector, double factor)
	{
		vector.mData[0] *= factor;
		vector.mData[1] *= factor;
		vector.mData[2] *= factor;
		return Vector3((float)vector.mData[0], (float)vector.mData[1], (float)vector.mData[2]);
	};

	auto GetTexture = [this](fbxsdk::FbxProperty& fbxProperty, int32 index) -> TComPtr<ID3D12Resource>
	{
		int32 numTextures = fbxProperty.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
		if (numTextures <= index)
		{
			return nullptr;
		}

		fbxsdk::FbxFileTexture* fileTexture = fbxProperty.GetSrcObject<fbxsdk::FbxFileTexture>(index);
		path relativeFilename = fileTexture->GetRelativeFileName();

		TRefPtr<String> fullpath = String::Format(L"{0}/{1}", parentPath.c_str(), relativeFilename.c_str());
		auto imageLoader = NewObject<COMImageLoader>(engine->GetCOMDevice(), fullpath);
		if (!imageLoader->IsValid)
		{
			TRefPtr<String> mediaName = fileTexture->GetMediaName().Buffer();
			SE_LOG(LogAssets, Warning, L"Failed to load texture file with path: {0}. Try search using media name.", fullpath);
			TRefPtr<String> mediaPath = String::Format(L"{0}/{1}", parentPath.c_str(), mediaName);
			imageLoader = NewObject<COMImageLoader>(engine->GetCOMDevice(), mediaPath);
			if (!imageLoader->IsValid)
			{
				SE_LOG(LogAssets, Warning, L"Failed to load texture file with media path: {0}. Search all directories using media name.", mediaPath);

				stack<path> path_stack;
				path_stack.push(parentPath);

				while (!path_stack.empty())
				{
					path curr = path_stack.top();
					path_stack.pop();
					for (path entry : directory_iterator(curr))
					{
						SE_LOG(LogAssets, Verbose, L"Path: {0}", entry.c_str());
						if (!entry.has_extension())
						{
							path_stack.push(entry);
							continue;
						}

						if (mediaName->Equals(entry.filename().c_str(), true))
						{
							imageLoader = NewObject<COMImageLoader>(engine->GetCOMDevice(), entry.c_str());
							stack<path> clear;
							path_stack.swap(clear);
							break;
						}
					}
				}

				if (!imageLoader->IsValid)
				{
					SE_LOG(LogAssets, Error, L"Failed to load texture with media filename: {0}", mediaPath);
					return nullptr;
				}
			}
		}

		auto imageFrame = imageLoader->GetFrame(0);
		auto converter = imageFrame->ConvertFormat(DXGI_FORMAT_R8G8B8A8_UNORM);

		return engine->GetDeviceBundle()->CreateTexture2D(converter.Get(), engine->GetPrimaryCommandQueue(), DXGI_FORMAT_R8G8B8A8_UNORM, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	};

	for (int32 i = 0; i < numMaterials; ++i)
	{
		TRefPtr<Material>& m = materials.emplace_back();
		m = NewObject<Material>(engine->GetDeviceBundle());

		fbxsdk::FbxSurfaceMaterial* surface = scene->GetMaterial(i);
		fbxsdk::FbxClassId surfaceClassId = surface->GetClassId();

		// Grab attributes of phong surface.
		if (surfaceClassId.Is(fbxsdk::FbxSurfacePhong::ClassId))
		{
			FbxSurfacePhong* phong = static_cast<FbxSurfacePhong*>(surface);
			m->Ambient = GetFactorVector(phong->Ambient, phong->AmbientFactor);
			m->Diffuse = GetFactorVector(phong->Diffuse, phong->DiffuseFactor);
			m->Specular = GetFactorVector(phong->Specular, phong->SpecularFactor);
			m->SpecExp = (float)phong->Shininess;
		}
		else if (surfaceClassId.Is(fbxsdk::FbxSurfaceLambert::ClassId))
		{
			FbxSurfaceLambert* phong = static_cast<FbxSurfaceLambert*>(surface);
			m->Ambient = GetFactorVector(phong->Ambient, phong->AmbientFactor);
			m->Diffuse = GetFactorVector(phong->Diffuse, phong->DiffuseFactor);
			m->Specular = 0;
			m->SpecExp = 0;
		}

		// Getting textures.
		if (fbxsdk::FbxProperty diffuseMap = surface->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse); diffuseMap.IsValid())
		{
			m->DiffuseMap = GetTexture(diffuseMap, 0).Get();
		}
		if (fbxsdk::FbxProperty normalMap = surface->FindProperty(fbxsdk::FbxSurfaceMaterial::sNormalMap); normalMap.IsValid())
		{
			m->NormalMap = GetTexture(normalMap, 0).Get();
		}
	}
	
	return true;
}

bool FbxParser::ProcessStaticMeshes()
{
	fbxsdk::FbxNode* root = scene->GetRootNode();
	return ProcessNode(root, Matrix4x4::Identity);
}

bool FbxParser::ProcessNode(fbxsdk::FbxNode* fbxNode, const Matrix4x4& m)
{
	// Make node transformation.
	const Matrix4x4 M = Matrix4x4::Multiply(m, AsMatrix4x4(fbxNode->EvaluateLocalTransform()));

	int32 numAttrs = fbxNode->GetNodeAttributeCount();
	for (int32 i = 0; i < numAttrs; ++i)
	{
		fbxsdk::FbxNodeAttribute* nodeAttr = fbxNode->GetNodeAttributeByIndex(i);
		fbxsdk::FbxNodeAttribute::EType attrType = nodeAttr->GetAttributeType();

		switch (attrType)
		{
		case fbxsdk::FbxNodeAttribute::eMesh:
			if (!ProcessStaticMesh(fbxNode, (fbxsdk::FbxMesh*)nodeAttr, M))
			{
				return false;
			}
			break;
		}
	}

	int32 numChilds = fbxNode->GetChildCount();
	for (int32 i = 0; i < numChilds; ++i)
	{
		ProcessNode(fbxNode->GetChild(i), M);
	}

	return true;
}

bool FbxParser::ProcessStaticMesh(fbxsdk::FbxNode* fbxNode, fbxsdk::FbxMesh* fbxMesh, const Matrix4x4& m)
{
	const fbxsdk::FbxVector4 T = fbxNode->GetGeometricTranslation(fbxsdk::FbxNode::eSourcePivot);
	const fbxsdk::FbxVector4 R = fbxNode->GetGeometricRotation(fbxsdk::FbxNode::eSourcePivot);
	const fbxsdk::FbxVector4 S = fbxNode->GetGeometricScaling(fbxsdk::FbxNode::eSourcePivot);
	Matrix4x4 M = Matrix4x4::Identity;

	if (int32 numDeformers = fbxMesh->GetDeformerCount(); numDeformers != 0)
	{
		// TEMPORAL IMPLEMENTATION
		for (int32 i = 0; i < numDeformers; ++i)
		{
			if (auto skin = (fbxsdk::FbxSkin*)fbxMesh->GetDeformer(i, fbxsdk::FbxDeformer::eSkin); skin != nullptr)
			{
				M = Matrix4x4::Multiply(m, AsMatrix4x4(fbxsdk::FbxAMatrix(T, R, S)));
			}
		}
	}

	// Read all control points.
	vector<Vector3> controlPoints(fbxMesh->GetControlPointsCount());
	for (size_t i = 0; i < controlPoints.size(); ++i)
	{
		controlPoints[i] = M.TransformVector(Vector4(AsVector3(fbxMesh->GetControlPoints()[i]), 1)).Cast<Vector3>();
	}

	int32 polygonCount = fbxMesh->GetPolygonCount();

	struct Layer
	{
		int32 ControlPointIndex;
		int32 TexCoordIndex;
		int32 NormalIndex;
	};
	map<uint64, int32> polys;

	// Read layers and compute direct array.
	fbxsdk::FbxLayerElementNormal* normalLayer = fbxMesh->GetElementNormal();
	fbxsdk::FbxLayerElementUV* texLayer = fbxMesh->GetElementUV();
	vector<Vector3> normalDirectArray;
	vector<Vector2> texDirectArray;

	if (normalLayer != nullptr)
	{
		fbxsdk::FbxLayerElementArrayTemplate<fbxsdk::FbxVector4>& directArray = normalLayer->GetDirectArray();
		normalDirectArray.resize(directArray.GetCount());

		for (int32 i = 0; i < directArray.GetCount(); ++i)
		{
			normalDirectArray[i] = M.TransformVector(Vector4(AsVector3(directArray[i]), 0)).Cast<Vector3>();
		}
	}

	if (texLayer != nullptr)
	{
		fbxsdk::FbxLayerElementArrayTemplate<fbxsdk::FbxVector2>& directArray = texLayer->GetDirectArray();
		texDirectArray.resize(directArray.GetCount());

		for (int32 i = 0; i < directArray.GetCount(); ++i)
		{
			texDirectArray[i] = AsVector2(directArray[i]);
		}
	}

	// Make instanced subset.
	InstancedSubset& instanced = subsets.emplace_back();

	// Construct vertex and index buffer.
	vector<Vertex>& vertexBuffer = instanced.VertexBuffer;
	vector<uint32>& indexBuffer = instanced.IndexBuffer;
	vertexBuffer.reserve(polygonCount * 3);
	indexBuffer.reserve(polygonCount * 3);

	for (int32 i = 0; i < polygonCount; ++i)
	{
		// Mesh is already triangulated.
		for (int32 j = 0; j < 3; ++j)
		{
			const int32 VertexCounter = i * 3 + j;

			Layer layer;
			layer.ControlPointIndex = fbxMesh->GetPolygonVertex(i, j);
			layer.TexCoordIndex = GetDirectIndex(texLayer, layer.ControlPointIndex, VertexCounter);
			layer.NormalIndex = GetDirectIndex(normalLayer, layer.ControlPointIndex, VertexCounter);
			const uint64 layerHash = GetHashCode(layer);

			// Find constructed layer index or create new layer index.
			if (auto it = polys.find(layerHash); it != polys.end())
			{
				indexBuffer.emplace_back(it->second);
			}
			else
			{
				int32 const NewIndex = (int32)polys.size();

				indexBuffer.emplace_back(NewIndex);
				polys.emplace(layerHash, NewIndex);

				// Construct new vertex.
				Vertex& v = vertexBuffer.emplace_back();

				v.Pos = controlPoints[layer.ControlPointIndex];
				v.TexCoord = GetDirectElement(texDirectArray, layer.TexCoordIndex);
				v.Normal = GetDirectElement(normalDirectArray, layer.NormalIndex);
			}
		}
	}

	if (fbxsdk::FbxLayerElementArrayTemplate<int32>* materialLayer; fbxMesh->GetMaterialIndices(&materialLayer))
	{
		const int32 num = materialLayer->GetCount();
		if (num < 1)
		{
			SE_LOG(LogAssets, Error, L"Mesh instance have not material layer. Mesh name: {0}", fbxMesh->GetName());
			return false;
		}

		instanced.MaterialIndex = materialLayer->GetAt(0);
	}
	else
	{
		SE_LOG(LogAssets, Error, L"Mesh instance have not material layer. Mesh name: {0}", fbxMesh->GetName());
		return false;
	}

	return true;
}

bool FbxParser::ComposeStaticMeshes()
{
	vector<Vertex> mergedVertexBuffer;
	vector<uint32> mergedIndexBuffer;

	vector<StaticMeshSubsetInfo> actualSubsets;
	actualSubsets.reserve(subsets.size());

	// Calc total vertex and index size for reserve allocation.
	size_t totalVertex = 0;
	size_t totalIndex = 0;
	for (size_t i = 0; i < subsets.size(); ++i)
	{
		InstancedSubset& item = subsets[i];
		totalVertex += item.VertexBuffer.size();
		totalIndex += item.IndexBuffer.size();

		// Emplace subset immediately for first subset instance.
		if (i == 0)
		{
			mergedVertexBuffer = move(item.VertexBuffer);
			mergedIndexBuffer = move(item.IndexBuffer);

			StaticMeshSubsetInfo& actualSubset = actualSubsets.emplace_back();
			actualSubset.VertexStart = 0;
			actualSubset.VertexCount = (uint32)totalVertex;
			actualSubset.IndexStart = 0;
			actualSubset.IndexCount = (uint32)totalIndex;
			actualSubset.Material = materials[item.MaterialIndex].Get();
		}
	}

	// Reserve and construct full mesh buffers.
	mergedVertexBuffer.reserve(totalVertex);
	mergedIndexBuffer.reserve(totalIndex);

	for (size_t i = 1; i < subsets.size(); ++i)
	{
		InstancedSubset& item = subsets[i];
		StaticMeshSubsetInfo& subset = actualSubsets.emplace_back();

		// Fill actual subset info.
		subset.VertexStart = (uint32)mergedVertexBuffer.size();
		subset.VertexCount = (uint32)item.VertexBuffer.size();
		subset.IndexStart = (uint32)mergedIndexBuffer.size();
		subset.IndexCount = (uint32)item.IndexBuffer.size();
		subset.Material = materials[item.MaterialIndex].Get();

		// Merge buffer.
		mergedVertexBuffer.resize(subset.VertexStart + subset.VertexCount);
		memcpy(mergedVertexBuffer.data() + subset.VertexStart, item.VertexBuffer.data(), sizeof(Vertex) * subset.VertexCount);
		mergedIndexBuffer.resize(subset.IndexStart + subset.IndexCount);
		memcpy(mergedIndexBuffer.data() + subset.IndexStart, item.IndexBuffer.data(), sizeof(uint32) * subset.IndexCount);
	}

	if (mergedVertexBuffer.size() == 0 || mergedIndexBuffer.size() == 0)
	{
		// Is not a static mesh.
		return true;
	}

	// Fill geometry data.
	StaticMeshGeometryData geometry;
	geometry.VertexBuffer = mergedVertexBuffer;
	geometry.IndexBuffer = mergedIndexBuffer;
	geometry.Subsets = actualSubsets;

	// Create static mesh.
	staticMesh = NewObject<StaticMesh>(engine, geometry);

	return true;
}

template<class TLayerElementTemplate>
int32 FbxParser::GetDirectIndex(TLayerElementTemplate* layer, int32 controlPointIndex, int32 vertexCounter) const
{
	auto mappingMode = layer->GetMappingMode();
	auto referenceMode = layer->GetReferenceMode();

	int mappingIndex{ };
	if (mappingMode == FbxGeometryElement::eByControlPoint)
		mappingIndex = controlPointIndex;
	else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
		mappingIndex = vertexCounter;  // UV is return vertexCountOrTextureIndex (?)

	int directIndex{ };
	if (referenceMode == FbxGeometryElement::eDirect)
		directIndex = mappingIndex;
	else if (referenceMode == FbxGeometryElement::eIndexToDirect)
		directIndex = layer->GetIndexArray().GetAt(mappingIndex);

	return directIndex;
}

template<class TElement>
TElement FbxParser::GetDirectElement(const vector<TElement>& directElementArray, int32 directIndex) const
{
	if (directElementArray.size() == 0)
	{
		return TElement();
	}
	else
	{
		return directElementArray[directIndex];
	}
}

Vector2 FbxParser::AsVector2(const fbxsdk::FbxVector2& vector2) const
{
	return Vector2((float)vector2.mData[0], (float)vector2.mData[1]);
}

Vector3 FbxParser::AsVector3(const fbxsdk::FbxVector4& vector4) const
{
	return Vector3((float)vector4.mData[0], (float)vector4.mData[1], (float)vector4.mData[2]);
}

Matrix4x4 FbxParser::AsMatrix4x4(const fbxsdk::FbxAMatrix& matrix) const
{
	return Matrix4x4(
		(float)matrix.Get(0, 0), (float)matrix.Get(0, 1), (float)matrix.Get(0, 2), (float)matrix.Get(0, 3),
		(float)matrix.Get(1, 0), (float)matrix.Get(1, 1), (float)matrix.Get(1, 2), (float)matrix.Get(1, 3),
		(float)matrix.Get(2, 0), (float)matrix.Get(2, 1), (float)matrix.Get(2, 2), (float)matrix.Get(2, 3),
		(float)matrix.Get(3, 0), (float)matrix.Get(3, 1), (float)matrix.Get(3, 2), (float)matrix.Get(3, 3)
	);
}

template<class T>
uint64 FbxParser::GetHashCode(const T& value) const
{
	return GetHashCode(sizeof(T), (const char*)&value);
}

size_t FbxParser::GetHashCode(size_t N, const char* S, size_t H) const
{
	return N > 0 ? GetHashCode(N - 1, S + 1, (H ^ *S) * FNV_Prime) : H;
}
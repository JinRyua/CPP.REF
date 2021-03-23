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

	// Convert scene to engine optimized.
	FbxGeometryConverter geometryConverter(manager);
	geometryConverter.Triangulate(scene, true);

	parentPath = path(filepath->C_Str).parent_path();
	if (!ProcessMaterials())
	{
		SE_LOG(LogAssets, Error, L"Cannot process materials from scene with file: {0}.", filepath);
		return false;
	}

	if (!ProcessStaticMeshes())
	{
		SE_LOG(LogAssets, Error, L"Cannot process static meshes from scene with file: {0}.", filepath);
		return false;
	}

	return true;
}

bool FbxParser::IsStaticMesh() const
{
	return true;
}

TRefPtr<StaticMesh> FbxParser::GetStaticMesh() const
{
	return nullptr;
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
	return true;
}
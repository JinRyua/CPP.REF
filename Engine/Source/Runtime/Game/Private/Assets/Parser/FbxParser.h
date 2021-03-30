// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "ParserBase.h"

#include <filesystem>
#include "Assets/FbxMinimal.h"
#include "SceneRendering/Vertex.h"

class Material;
class Engine;

class FbxParser : public ParserBase
{
public:
	using Super = Object;

private:
	struct InstancedSubset
	{
		std::vector<Vertex> VertexBuffer;
		std::vector<uint32> IndexBuffer;
		int32 MaterialIndex;
	};

private:
	Engine* const engine;
	fbxsdk::FbxManager* const manager;
	fbxsdk::FbxImporter* importer;
	fbxsdk::FbxScene* scene;
	std::filesystem::path parentPath;

	std::vector<TRefPtr<Material>> materials;
	std::vector<InstancedSubset> subsets;
	TRefPtr<StaticMesh> staticMesh;
	
public:
	FbxParser(Engine* engine, fbxsdk::FbxManager* fbxMgr);
	~FbxParser() override;

	bool TryParse(TRefPtr<String> filepath) override;

	bool IsStaticMesh() const override;
	TRefPtr<StaticMesh> GetStaticMesh() const override;

private:
	bool ProcessMaterials();
	bool ProcessStaticMeshes();
	
	bool ProcessNode(fbxsdk::FbxNode* fbxNode, const Matrix4x4& m);

	bool ProcessStaticMesh(fbxsdk::FbxNode* fbxNode, fbxsdk::FbxMesh* fbxMesh, const Matrix4x4& m);
	bool ComposeStaticMeshes();

	template<class TLayerElementTemplate>
	int32 GetDirectIndex(TLayerElementTemplate* layer, int32 controlPointIndex, int32 vertexCounter) const;
	template<class TElement>
	TElement GetDirectElement(const std::vector<TElement>& directElementArray, int32 directIndex) const;

	Vector2 AsVector2(const fbxsdk::FbxVector2& vector2) const;
	Vector3 AsVector3(const fbxsdk::FbxVector4& vector4) const;
	Matrix4x4 AsMatrix4x4(const fbxsdk::FbxAMatrix& matrix) const;

private:
	constexpr static size_t FNV_Prime = 1099511628211ULL;
	constexpr static size_t FNV_Basis = 14695981039346656037ULL;

	template<class T>
	uint64 GetHashCode(const T& value) const;
	uint64 GetHashCode(size_t N, const char* S, size_t H = FNV_Basis) const;
};
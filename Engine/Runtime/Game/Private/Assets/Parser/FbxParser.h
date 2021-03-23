// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "ParserBase.h"

#include "Assets/FbxMinimal.h"
#include <filesystem>

class Material;
class Engine;

class FbxParser : public ParserBase
{
public:
	using Super = Object;

private:
	Engine* const engine;
	fbxsdk::FbxManager* const manager;
	fbxsdk::FbxImporter* importer;
	fbxsdk::FbxScene* scene;
	std::filesystem::path parentPath;

	std::vector<TRefPtr<Material>> materials;
	
public:
	FbxParser(Engine* engine, fbxsdk::FbxManager* fbxMgr);
	~FbxParser() override;

	bool TryParse(TRefPtr<String> filepath) override;

	bool IsStaticMesh() const override;
	TRefPtr<StaticMesh> GetStaticMesh() const override;

private:
	bool ProcessMaterials();
	bool ProcessStaticMeshes();
};
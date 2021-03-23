// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Assets/AssetImporter.h"

#include <Path.h>
#include "FbxInstance.h"
#include "Parser/AssimpParser.h"
#include "Parser/FbxParser.h"
#include "SceneRendering/StaticMesh.h"

AssetImporter::AssetImporter(Engine* engine) : Super()
	, engine(engine)
{
	fbxInstance = NewObject<FbxInstance>();
}

AssetImporter::~AssetImporter()
{

}

TRefPtr<StaticMesh> AssetImporter::ImportStaticMesh(TRefPtr<String> path)
{
	TRefPtr<String> ext = Path::GetExtension(path);
	if (ext->Equals(L".fbx", true))
	{
		// Is fbx try parse, if failed, process as assimp.
		FbxParser parser(engine, fbxInstance->GetManager());
		if (parser.TryParse(path))
		{
			return parser.GetStaticMesh();
		}
	}

	AssimpParser parser(engine);
	if (!parser.TryParse(path))
	{
		return nullptr;
	}

	return parser.GetStaticMesh();
}
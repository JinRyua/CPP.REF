// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "FbxInstance.h"

#include <fbxsdk.h>

FbxInstance::FbxInstance() : Super()
	, manager(nullptr)
{
	manager = fbxsdk::FbxManager::Create();
}

FbxInstance::~FbxInstance()
{
	if (manager != nullptr)
	{
		manager->Destroy();
		manager = nullptr;
	}
}

fbxsdk::FbxManager* FbxInstance::GetManager() const
{
	return manager;
}
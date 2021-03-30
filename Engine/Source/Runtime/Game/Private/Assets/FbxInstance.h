// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"

#include "FbxMinimal.h"

class FbxInstance : virtual public Object
{
public:
	using Super = Object;

private:
	fbxsdk::FbxManager* manager;

public:
	FbxInstance();
	~FbxInstance() override;

	fbxsdk::FbxManager* GetManager() const;
};
﻿// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"

struct LogCategoryBase;

enum class TickingGroup
{
	PrePhysics = 0,
	DuringPhysics = 1,
	PostPhysics = 2,
	PostUpdateWork = 3
};

struct GAME_API TickFunction
{
	using This = TickFunction;

	static LogCategoryBase LogTicking;

	bool bCanEverTick : 1;
	TickingGroup TickGroup;
	std::chrono::duration<double> TickInterval;

	TickFunction();
	~TickFunction();

	virtual void ExecuteTick(std::chrono::duration<double> deltaTime) = 0;
};
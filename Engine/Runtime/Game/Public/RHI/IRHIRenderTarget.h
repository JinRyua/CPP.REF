﻿// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"

interface IRHICommandList;

interface GAME_API IRHIRenderTarget : virtual public Object
{
	virtual void ResizeBuffers(int32 width, int32 height) = 0;
	virtual size_t GetRenderTargetCount() const = 0;
};
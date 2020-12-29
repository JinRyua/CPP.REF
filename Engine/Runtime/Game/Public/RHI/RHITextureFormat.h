﻿// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"

namespace SC::Runtime::Game::RHI
{
	enum class RHITextureFormat
	{
		Unknown,
		R8G8B8A8_UNORM
	};
}

#ifdef __SC_GLOBAL_NAMESPACE__
using SC::Runtime::Game::RHI::RHITextureFormat;
#endif
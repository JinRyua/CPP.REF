// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

class HashHelper abstract final
{
	HashHelper() = delete;

public:
	static size_t GetHashCode(float value);
	static size_t GetHashCode(const char* name);
};
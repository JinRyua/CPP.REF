// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

/// <summary>
/// 스레드 안전한 원자 연산을 수행하는 함수를 제공합니다.
/// </summary>
SCLASS(SInterlocked) class CORE_API SInterlocked : virtual public SObject
{
	SCLASS_BODY(SInterlocked)

private:
	SInterlocked() = delete;

public:
	static int64 Increment64(int64& value);
	static int64 Decrement64(int64& value);
};
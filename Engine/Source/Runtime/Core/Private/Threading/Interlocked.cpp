// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Threading/Interlocked.h"

#undef interface
#include <Windows.h>

int64 SInterlocked::Increment64(int64& value)
{
	return InterlockedIncrement64((volatile long long*)&value);
}

int64 SInterlocked::Decrement64(int64& value)
{
	return InterlockedDecrement64((volatile long long*)&value);
}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/TRefPtr.h"

#include "Exception/InvalidCastException.h"
#include "Exception/NullReferenceException.h"

[[noreturn]] void ThrowInvalidCastException()
{
	throw new SInvalidCastException();
}

[[noreturn]] void ThrowNullReferenceException()
{
	throw new SNullReferenceException();
}
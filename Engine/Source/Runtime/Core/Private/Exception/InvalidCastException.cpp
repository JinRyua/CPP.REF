// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/InvalidCastException.h"

#include "Core/String.h"

SInvalidCastException::SInvalidCastException() : Super("Invalid cast detected."_s)
{

}

SInvalidCastException::SInvalidCastException(SString* message) : Super(message)
{

}

SInvalidCastException::SInvalidCastException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SInvalidCastException::~SInvalidCastException()
{

}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/IndexOutOfRangeException.h"

#include "Core/String.h"

SIndexOutOfRangeException::SIndexOutOfRangeException() : Super("Index out of range."_s)
{

}

SIndexOutOfRangeException::SIndexOutOfRangeException(SString* message) : Super(message)
{

}

SIndexOutOfRangeException::SIndexOutOfRangeException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SIndexOutOfRangeException::~SIndexOutOfRangeException()
{

}
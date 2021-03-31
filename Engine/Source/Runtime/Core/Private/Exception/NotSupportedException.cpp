// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/NotSupportedException.h"

#include "Core/String.h"

SNotSupportedException::SNotSupportedException() : Super("Feature is not supported."_s)
{

}

SNotSupportedException::SNotSupportedException(SString* message) : Super(message)
{

}

SNotSupportedException::SNotSupportedException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SNotSupportedException::~SNotSupportedException()
{

}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/ArgumentException.h"
SCLASS_BODY_IMPL(SArgumentException);

#include "Core/String.h"

SArgumentException::SArgumentException() : Super("Invalid argument detected."_s)
{

}

SArgumentException::SArgumentException(SString* message) : Super(message)
{

}

SArgumentException::SArgumentException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SArgumentException::~SArgumentException()
{

}
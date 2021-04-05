// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/InvalidOperationException.h"

#include "Core/String.h"

SInvalidOperationException::SInvalidOperationException() : Super("Invalid operation detected."_s)
{

}

SInvalidOperationException::SInvalidOperationException(SString* message) : Super(message)
{

}

SInvalidOperationException::SInvalidOperationException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SInvalidOperationException::~SInvalidOperationException()
{

}
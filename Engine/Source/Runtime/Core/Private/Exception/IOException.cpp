// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/IOException.h"
SCLASS_BODY_IMPL(SIOException);

#include "Core/String.h"

SIOException::SIOException() : Super("Invalid argument detected."_s)
{

}

SIOException::SIOException(SString* message) : Super(message)
{

}

SIOException::SIOException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SIOException::~SIOException()
{

}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/ArgumentNullException.h"

#include "Core/String.h"

SArgumentNullException::SArgumentNullException() : Super("Null argument detected."_s)
{

}

SArgumentNullException::SArgumentNullException(SString* message) : Super(message)
{

}

SArgumentNullException::SArgumentNullException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SArgumentNullException::~SArgumentNullException()
{

}
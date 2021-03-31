// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/FormatException.h"

#include "Core/String.h"

SFormatException::SFormatException() : Super("Invalid format or argument detected."_s)
{

}

SFormatException::SFormatException(SString* message) : Super(message)
{

}

SFormatException::SFormatException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SFormatException::~SFormatException()
{

}
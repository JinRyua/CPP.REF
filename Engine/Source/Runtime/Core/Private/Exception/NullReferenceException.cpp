// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/NullReferenceException.h"
SCLASS_BODY_IMPL(SNullReferenceException);

#include "Core/String.h"

SNullReferenceException::SNullReferenceException() : Super("Null reference detected."_s)
{

}

SNullReferenceException::SNullReferenceException(SString* message) : Super(message)
{

}

SNullReferenceException::SNullReferenceException(SString* message, SException* innerException) : Super(message, innerException)
{

}

SNullReferenceException::~SNullReferenceException()
{

}
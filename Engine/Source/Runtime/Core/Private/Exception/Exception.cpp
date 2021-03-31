// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Exception/Exception.h"

#include "Core/String.h"

SException::SException() : Super()
{
	innerException = nullptr;
	message = "Unexpected error."_s;
}

SException::SException(SString* message) : Super()
{
	innerException = nullptr;
	this->message = message;
}

SException::SException(SString* message, SException* innerSException)
{
	this->innerException = innerException;
	this->message = message;
}

SException::~SException()
{

}

SString* SException::GetMessage() const
{
	return message;
}

SException* SException::GetInnerException() const
{
	return innerException;
}
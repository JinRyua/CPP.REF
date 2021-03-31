// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/Type.h"

SType::SType() : Super(true)
{

}

SType::~SType()
{

}

SString* SType::ToString() const
{
	return classNameObj;
}

size_t SType::GetHashCode() const
{
	return hashCode;
}

size_t SType::GetRTTIHashCode() const
{
	return rttiType;
}

const char* SType::GetNativeString() const
{
	return className;
}

size_t SType::GetPropertyCount() const
{
	return propertyCount;
}

SObject* SType::Activate()
{
	return activator();
}

void* SType::operator new(size_t length)
{
	// Save 1024 types.
	static thread_local int8 storage[sizeof(SType) * 1024];
	static thread_local size_t seek = 0;

	int8* ptr = storage + seek;
	seek += sizeof(SType);

	return ptr;
}
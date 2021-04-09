// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Reflection/Field.h"
SCLASS_BODY_IMPL(SField);

#include "Core/String.h"
#include "Core/Type.h"
#include "Exception/InvalidCastException.h"

inline size_t& GetFieldPointer(void* ptr, ssize_t offset)
{
	return *(size_t*)((int8*)ptr + offset);
}

SField::SField() : Super(true)
	, fieldName(nullptr)
	, fieldToType(0)
	, rttiType(0)
	, cachedFieldType(nullptr)
{
}

SField::~SField()
{
}

SType* SField::GetFieldType() const
{
	return GetCachedType();
}

SString* SField::GetFieldName() const
{
	return new SString(fieldName);
}

void SField::SetValue(SObject* instance, SObject* value)
{
	void* instance_ptr = parent->objectToType(instance);
	size_t& fieldPtr = GetFieldPointer(instance_ptr, fieldToType);
	fieldPtr = (size_t)objectToType(value);
}

SObject* SField::GetValue(SObject* instance) const
{
	SType* fieldType = GetCachedType();
	if (fieldType == nullptr)
	{
		throw new SInvalidCastException();
	}

	void* instance_ptr = parent->objectToType(instance);
	size_t& fieldPtr = GetFieldPointer(instance_ptr, fieldToType);
	return typeToObject((void*)fieldPtr);
}

void* SField::operator new(size_t length)
{
	// Save 8192 properties.
	static thread_local int8 storage[sizeof(SField) * 8192];
	static thread_local size_t seek = 0;

	int8* ptr = storage + seek;
	seek += sizeof(SField);

	return ptr;
}

SType* SField::GetCachedType() const
{
	if (cachedFieldType == nullptr)
	{
		cachedFieldType = TypeCollection::GetType(rttiType);
	}
	return cachedFieldType;
}
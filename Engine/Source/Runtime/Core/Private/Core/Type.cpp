// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/Type.h"
SCLASS_BODY_IMPL(SType);

#include <string_view>
#include "Core/String.h"
#include "Reflection/Field.h"

using namespace std;

SType::SType() : Super(true)
	, className(nullptr)
	, hashCode(0)
{

}

SType::~SType()
{

}

SString* SType::ToString() const
{
	return new SString(className);
}

size_t SType::GetHashCode() const
{
	return hashCode;
}

const char* SType::GetNativeString() const
{
	return className;
}

size_t SType::GetPropertyCount() const
{
	return memberDeclares.size();
}

SObject* SType::Activate()
{
	return activator();
}

SType* SType::GetSuper() const
{
	return TypeCollection::GetType(superRtti);
}

SField* SType::GetField(const char* name)
{
	for (size_t i = 0; i < fields.size(); ++i)
	{
		if (string_view(fields[i]->fieldName) == string_view(name))
		{
			return fields[i];
		}
	}

	return nullptr;
}

SField* SType::GetField(SString* name)
{
	return GetField(name->AsMultiByte().c_str());
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

void SType::RegisterFields()
{
	for (size_t i = 0; i < memberDeclares.size(); ++i)
	{
		SField* field = new SField();
		auto& declare = memberDeclares[i];

		field->parent = this;
		field->fieldName = declare.Name;
		field->fieldToType = declare.Offset;
		field->rttiType = declare.FieldType;
		field->typeToObject = declare.TypeToObject;
		field->objectToType = declare.ObjectToType;

		fields.emplace_back(field);
	}
}
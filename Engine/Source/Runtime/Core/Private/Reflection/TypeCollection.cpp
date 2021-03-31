// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Reflection/TypeCollection.h"

#include <utility>
#include "Core/Type.h"

using namespace std;

map<size_t, SType*>* TypeCollection::TypeRegisterBase::typeCollection;
map<size_t, size_t>* TypeCollection::TypeRegisterBase::rttiToUniqueType;
map<string, size_t>* TypeCollection::TypeRegisterBase::nameToUniqueType;

TypeCollection::TypeRegisterBase::TypeRegisterBase()
{
	static map<size_t, SType*> typeCollection_Impl;
	static map<size_t, size_t> rttiToUniqueType_Impl;
	static map<string, size_t> nameToUniqueType_Impl;

	typeCollection = &typeCollection_Impl;
	rttiToUniqueType = &rttiToUniqueType_Impl;
	nameToUniqueType = &nameToUniqueType_Impl;

	typeCollection->emplace(0, nullptr);
}

TypeCollection::TypeRegisterBase::~TypeRegisterBase()
{

}

SType* TypeCollection::GetType(size_t uniqueType)
{
	if (auto it = TypeRegisterBase::typeCollection->find(uniqueType); it != TypeRegisterBase::typeCollection->end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

SType* TypeCollection::GetTypeByRTTI(const type_info& rtti)
{
	if (auto it = TypeRegisterBase::rttiToUniqueType->find(rtti.hash_code()); it != TypeRegisterBase::rttiToUniqueType->end())
	{
		return GetType(it->second);
	}
	else
	{
		return nullptr;
	}
}

SType* TypeCollection::GetTypeByName(const char* typeName)
{
	if (auto it = TypeRegisterBase::nameToUniqueType->find(typeName); it != TypeRegisterBase::nameToUniqueType->end())
	{
		return GetType(it->second);
	}
	else
	{
		return nullptr;
	}
}

SType* TypeCollection::GetTypeByName(SString* typeName)
{
	return GetTypeByName(typeName->AsMultiByte().c_str());
}

void TypeCollection::AddType(const char* className, size_t hashCode, const type_info& rttiType, function<SObject*()> activator)
{
	SType* type = new SType();
	type->className = className;
	type->hashCode = hashCode;
	type->rttiType = rttiType.hash_code();
	type->activator = move(activator);

	TypeRegisterBase::typeCollection->emplace(hashCode, type);
	TypeRegisterBase::rttiToUniqueType->emplace(rttiType.hash_code(), hashCode);
	TypeRegisterBase::nameToUniqueType->emplace(className, hashCode);
}
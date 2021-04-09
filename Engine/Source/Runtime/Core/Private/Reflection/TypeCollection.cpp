// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Reflection/TypeCollection.h"

#include <utility>
#include "Core/Type.h"
#include "Core/String.h"

using namespace std;

map<size_t, SType*>* TypeCollection::TypeRegisterBase::typeCollection;
map<string, size_t>* TypeCollection::TypeRegisterBase::nameToType;

TypeCollection::TypeRegisterBase::TypeRegisterBase()
{
	static map<size_t, SType*> typeCollection_Impl;
	static map<string, size_t> nameToType_Impl;

	typeCollection = &typeCollection_Impl;
	nameToType = &nameToType_Impl;
}

TypeCollection::TypeRegisterBase::~TypeRegisterBase()
{

}

void TypeCollection::TypeRegisterBase::Register()
{
	SType* type = new SType();

	typeCollection->emplace(RttiTypeId, type);
	nameToType->emplace(ClassName, RttiTypeId);

	type->hashCode = RttiTypeId;
	type->className = ClassName;
	type->typeToObject = TypeToObject;
	type->objectToType = ObjectToType;
	type->activator = Activator;

	TypeRegisterBase* parent = this;

	for (; parent != nullptr;)
	{
		type->memberDeclares.insert(type->memberDeclares.end(), parent->MemberDeclares.begin(), parent->MemberDeclares.end());
		parent = parent->SuperClass;
	}

	type->RegisterFields();
}

SType* TypeCollection::GetType(size_t rtti)
{
	if (auto it = TypeRegisterBase::typeCollection->find(rtti); it != TypeRegisterBase::typeCollection->end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

SType* TypeCollection::GetTypeByName(const char* typeName)
{
	if (auto it = TypeRegisterBase::nameToType->find(typeName); it != TypeRegisterBase::nameToType->end())
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
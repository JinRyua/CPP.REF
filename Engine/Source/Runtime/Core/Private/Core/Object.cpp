// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/Object.h"

#include "Core/TGCRoot.h"
#include "Core/String.h"
#include "Core/GarbageCollector.h"
#include "Core/Type.h"
#include "Threading/Interlocked.h"
#include "Reflection/TypeCollection.h"

#if WITH_DEBUG
size_t SObject::ObjCount;
#endif

template<size_t Index>
consteval auto SObject::TypeRegisterImpl::GetPropertyCountImpl()
{
	constexpr bool b = SObject::template SPROPERTY_GetPropertyCounter<Index>();
	if constexpr (b)
	{
		return GetPropertyCountImpl<Index + 1>();
	}
	else
	{
		return Index;
	}
}

consteval size_t SObject::TypeRegisterImpl::GetPropertyCount()
{
	return GetPropertyCountImpl<0>();
}

template<size_t Count>
auto SObject::TypeRegisterImpl::GetPropertyChain() -> std::array<Reflection::SPropertyMemberDeclare, Count>
{
	return GetPropertyChainImpl(std::make_index_sequence<Count>{});
}

template<size_t... Indexes>
auto SObject::TypeRegisterImpl::GetPropertyChainImpl(std::index_sequence<Indexes...>&&) -> std::array<Reflection::SPropertyMemberDeclare, sizeof...(Indexes)>
{
	return { SObject::template SPROPERTY_GetPropertyChain<Indexes>()... };
}

SObject::TypeRegisterImpl::TypeRegisterImpl()
{
	RttiTypeId = typeid(This).hash_code();
	ClassName = Name;
	TypeToObject = Reflection::TypeToObject<This>();
	ObjectToType = Reflection::ObjectToType<This>();
	Activator = []() { return new This(); };
	SuperClass = nullptr;
	
	auto PropertyChain = GetPropertyChain<GetPropertyCount()>();
	MemberDeclares.reserve(PropertyChain.size());
	
	for (size_t i = 0; i < PropertyChain.size(); ++i)
	{
		MemberDeclares.emplace_back(PropertyChain[i]);
	}
	
	Register();
}

SObject::TypeRegisterImpl SObject::TypeRegister;

SObject::SObject() : This(false)
{

}

SObject::~SObject()
{
	if (bReferenceCollectiong)
	{
		GarbageCollector::RemoveReference(this);

#if WITH_DEBUG
		Interlocked::Decrement64((int64&)ObjCount);
#endif
	}
}

SString* SObject::ToString() const
{
	return GetType()->ToString();
}

bool SObject::Equals(SObject* right) const
{
	return this == right;
}

size_t SObject::GetHashCode() const
{
	return (size_t)this;
}

SType* SObject::GetType() const
{
	if (cachedType == nullptr)
	{
		cachedType = TypeCollection::GetType(typeid(*this));
	}
	return cachedType;
}

bool SObject::operator ==(SObject* right) const
{
	return this == right;
}

bool SObject::operator !=(SObject* right) const
{
	return this != right;
}

#if WITH_DEBUG

size_t SObject::GetObjectCount()
{
	return ObjCount;
}

#endif

SObject::SObject(bool bNoReferenceCollect)
	: bReferenceCollectiong(!bNoReferenceCollect)
	, cachedType(nullptr)
{
	if (bReferenceCollectiong)
	{
		GarbageCollector::AddReference(this);

#if WITH_DEBUG
		Interlocked::Increment64((int64&)ObjCount);
#endif
	}
}
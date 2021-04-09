// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/Object.h"

#include "Core/TRefPtr.h"
#include "Core/String.h"
#include "Core/ReferenceCollector.h"
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
	SuperClass = &Super::TypeRegister;
	
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
	if (weak_references != nullptr)
	{
		if (weak_references->weakReferences == 0)
		{
			delete weak_references;
			weak_references = nullptr;
		}
		else
		{
			weak_references->Invalidate();
		}
	}

	if (bReferenceCollectiong)
	{
		ReferenceCollector::RemoveReference(this);

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
	return TypeCollection::GetType(typeid(*this));
}

bool SObject::operator ==(SObject* right) const
{
	return this == right;
}

bool SObject::operator !=(SObject* right) const
{
	return this != right;
}

void SObject::AddRef()
{
	ref_count += 1;
}

void SObject::Release()
{
	if ((ref_count -= 1) == 0)
	{
		if (!bLockCollecting)
		{
			delete this;
		}
	}
}

void SObject::AddRefInterlocked()
{
	Interlocked::Increment64((int64&)ref_count);
}

void SObject::ReleaseInterlocked()
{
	size_t decremented = (size_t)Interlocked::Decrement64((int64&)ref_count);
	if (decremented == 0)
	{
		if (!bLockCollecting)
		{
			delete this;
		}
	}
}

WeakReferences* SObject::GetWeakReferences() const
{
	if (weak_references == nullptr)
	{
		weak_references = new WeakReferences();
	}
	return weak_references;
}

size_t SObject::GetReferenceCount() const
{
	return ref_count;
}

#if WITH_DEBUG

size_t SObject::GetObjectCount()
{
	return ObjCount;
}

#endif

SObject::SObject(bool bNoReferenceCollect)
	: bLockCollecting(false)
	, bReferenceCollectiong(!bNoReferenceCollect)
	, ref_count(0)
	, weak_references(nullptr)
{
	if (bReferenceCollectiong)
	{
		ReferenceCollector::AddReference(this);

#if WITH_DEBUG
		Interlocked::Increment64((int64&)ObjCount);
#endif
	}
}
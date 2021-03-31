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
		SInterlocked::Decrement64((int64&)ObjCount);
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
	return TypeCollection::GetTypeByRTTI(typeid(*this));
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
	SInterlocked::Increment64((int64&)ref_count);
}

void SObject::ReleaseInterlocked()
{
	size_t decremented = (size_t)SInterlocked::Decrement64((int64&)ref_count);
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
		SInterlocked::Increment64((int64&)ObjCount);
#endif
	}
}
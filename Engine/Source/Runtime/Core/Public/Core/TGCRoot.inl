// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Exception/InvalidCastException.h"
#include "Exception/NullReferenceException.h"
#include "Core/GarbageCollector.h"
	
template<TIsNotPointer T>
inline TGCRoot<T>::TGCRoot(T* ptr)
{
	if (ptr != nullptr)
	{
		this->ptr = const_cast<std::remove_const_t<T>*>(ptr);
		GC::MoveReferenceToGCRoot(ptr);
	}
}

template<TIsNotPointer T>
inline TGCRoot<T>::TGCRoot(TGCRoot&& ptr)
{
	this->ptr = ptr.ptr;
	ptr.ptr = nullptr;
}

template<TIsNotPointer T>
inline TGCRoot<T>::~TGCRoot()
{
	SafeRelease();
}

template<TIsNotPointer T> template<TIsBaseOf<T> O>
inline TGCRoot<T>::TGCRoot(TGCRoot<O>&& ptr)
	: This()
{
	this->ptr = ptr.ptr;
	ptr.ptr = nullptr;
}

template<TIsNotPointer T> template<TIsBaseOf<T> O>
inline TGCRoot<T>::TGCRoot(TGCRoot<const O>&& ptr)
	: This()
{
	this->ptr = const_cast<O*>(ptr.ptr);
	ptr.ptr = nullptr;
}

template<TIsNotPointer T>
inline void TGCRoot<T>::Reset()
{
	SafeRelease();
}

template<TIsNotPointer T>
inline T* TGCRoot<T>::Get() const
{
	return ptr;
}

template<TIsNotPointer T> template<TIsRefCore O>
inline bool TGCRoot<T>::Is(O** ptr) const
{
	O* cast = dynamic_cast<O*>(this->ptr);
	if (cast == nullptr)
	{
		if (ptr != nullptr)
		{
			*ptr = nullptr;
		}
		return false;
	}

	if (ptr != nullptr)
	{
		*ptr = cast;
		cast->AddRef();
	}

	return true;
}

template<TIsNotPointer T> template<TIsRefCore O>
inline O* TGCRoot<T>::As() const
{
	auto ret = TryAs<O>();
	if (!ret.IsValid_get())
	{
		throw new SInvalidCastException();
	}
	return std::move(ret);
}

template<TIsNotPointer T> template<TIsRefCore O>
inline O* TGCRoot<T>::TryAs() const
{
	O* cast = dynamic_cast<O*>(this->ptr);
	if (cast == nullptr)
	{
		return nullptr;
	}

	return cast;
}

template<TIsNotPointer T>
inline bool TGCRoot<T>::IsValid() const
{
	return ptr != nullptr;
}

template<TIsNotPointer T>
inline T* TGCRoot<T>::operator->() const
{
	return Get();
}

template<TIsNotPointer T>
inline TGCRoot<T>::operator bool() const
{
	return IsValid();
}

template<TIsNotPointer T>
inline void TGCRoot<T>::SafeRelease()
{
	if (ptr != nullptr)
	{
		GC::RemoveReferenceFromGCRoot(ptr);
		ptr = nullptr;
	}
}
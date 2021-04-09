// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#pragma warning(disable: 4251)

#include "CoreConcepts.h"

template<TIsNotPointer T>
class TGCRoot
{
	friend class SObject;
	template<TIsNotPointer O>
	friend class TGCRoot;

public:
	using Type = T;
	using This = TGCRoot;

private:
	mutable std::remove_const_t<T>* ptr;

	TGCRoot(const TGCRoot&) = delete;
	TGCRoot& operator=(const TGCRoot&) = delete;

public:
	inline TGCRoot(T* ptr);
	inline TGCRoot(TGCRoot&& ptr);
	inline ~TGCRoot();

	template<TIsBaseOf<T> O>
	inline TGCRoot(TGCRoot<O>&& ptr);
	template<TIsBaseOf<T> O>
	inline TGCRoot(TGCRoot<const O>&& ptr);

	inline void Reset();

	[[nodiscard]] inline T* Get() const;

	template<TIsRefCore O>
	[[nodiscard]] inline bool Is(O** ptr = nullptr) const;
	template<TIsRefCore O>
	[[nodiscard]] inline O* As() const;
	template<TIsRefCore O>
	[[nodiscard]] inline O* TryAs() const;

	inline bool IsValid() const;

	[[nodiscard]] inline T* operator->() const;
	[[nodiscard]] inline operator bool() const;

private:
	inline void SafeRelease();
};

#include "TGCRoot.inl"
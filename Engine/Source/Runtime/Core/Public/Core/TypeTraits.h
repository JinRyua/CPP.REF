// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

template<class T>
struct TRemoveConst
{
	using Type = T;
};

template<class T>
struct TRemoveConst<const T>
{
	using Type = T;
};

template<class T>
struct TRemoveReference
{
	using Type = T;
};

template<class T>
struct TRemoveReference<T&>
{
	using Type = T;
};

template<class T>
struct TRemoveReference<const T&>
{
	using Type = T;
};

template<class T>
struct TRemovePointer
{
	using Type = T;
};

template<class T>
struct TRemovePointer<T*>
{
	using Type = T;
};

template<class T>
struct TRemovePointer<const T*>
{
	using Type = T;
};

template<class T>
struct TRemovePointer<const T* const>
{
	using Type = T;
};

template<class TLeft, class TRight>
struct TIsSame
{
	static constexpr bool Value = false;
};

template<class T>
struct TIsSame<T, T>
{
	static constexpr bool Value = true;
};

template<class T>
struct TIsPointer
{
	static constexpr bool Value = false;
};

template<class T>
struct TIsPointer<T*>
{
	static constexpr bool Value = true;
};

template<class T>
struct TIsPointer<const T*>
{
	static constexpr bool Value = true;
};

template<class T>
struct TIsPointer<const T* const>
{
	static constexpr bool Value = true;
};
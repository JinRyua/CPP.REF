// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/CoreTypes.h"
#include "Core/TypeTraits.h"

class SObject;
class SString;

template<class TDerived, class TBase>
concept TIsBaseOf = requires(TBase* Base, TDerived* Derived)
{
	{ Base = Derived };
};

template<class TAssign, class TBase>
concept TIsAssignable = requires(TBase Base, TAssign Assign)
{
	{ Base = Assign };
};

template<class T>
concept TIsRefCore = TIsBaseOf<T, SObject> || TIsBaseOf<T, SString>;

template<class TChar>
concept TIsChar =
	TIsSame<typename TRemoveConst<TChar>::Type, char>::Value ||
	TIsSame<typename TRemoveConst<TChar>::Type, wchar_t>::Value;

template<class T>
concept TIsNotPointer = !TIsPointer<T>::Value;

template<class TPrim>
concept TIsPrimitive =
	TIsSame<typename TRemoveConst<TPrim>::Type, uint8>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, uint16>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, uint32>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, uint64>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, int8>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, int16>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, int32>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, int64>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, float>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, float>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, bool>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, char>::Value ||
	TIsSame<typename TRemoveConst<TPrim>::Type, wchar_t>::Value;

template<class TCallable>
concept TIsCallable = requires(TCallable Callable)
{
	{ Callable() };
};

template<class TIndexable, class TArg>
concept TIsIndexer = requires(TIndexable Indexable, TArg Index)
{
	{ Indexable[Index] };
};

template<class T, class... TArgs>
concept THasConstructor = requires(TArgs... args)
{
	{ T(args...) };
};

template<class TLeft, class TRight>
concept TIsSameWithoutDeco = TIsSame<
	typename TRemoveConst<typename TRemoveReference<TLeft>::Type>::Type,
	typename TRemoveConst<typename TRemoveReference<TRight>::Type>::Type
>::Value;

template<class TIterator, class T>
concept TIsIterator =
	TIsSameWithoutDeco<decltype(*TIterator()), T> &&
	requires(TIterator& It)
	{
		{ (T)*(++It) };
	} &&
	requires(TIterator& It)
	{
		{ (T)*(It++) };
	} &&
	requires(TIterator& It)
	{
		{ (size_t)(It - It) };
	};

template<class TStringArg>
concept TIsStringConstructible =
	TIsAssignable<TStringArg, const char*> ||
	TIsAssignable<TStringArg, const wchar_t*>;

template<class T>
concept THasConstIterator = requires()
{
	{ typename T::ConstIterator() };
};

template<class T>
concept THasIterator = THasConstIterator<T> && requires()
{
	{ typename T::Iterator() };
};

template<class T, class O>
concept TIsConvertible = requires(T Arg)
{
	{ (O)Arg };
};

template<class T>
concept TIsVectorType = requires(T Arg, const T ConstArg)
{
	{ ConstArg.GetComponentOrDefault(0) };
	{ (bool)ConstArg.Contains(0) };
	{ (float)ConstArg[0] };
	{ (size_t)ConstArg.Count };
};

template<class T, class O>
concept TIsSmallThen = sizeof(T) < sizeof(O);

template<class T, class O>
concept TIsGreaterEqualsThen = sizeof(T) >= sizeof(O);

template<class T, class O>
concept TComparable_Less = requires(T lh, O rh)
{
	{ lh < rh };
};

template<class T, class O>
concept TComparable_LessEquals = requires(T lh, O rh)
{
	{ lh <= rh };
};

template<class T, class O>
concept TComparable_Greater = requires(T lh, O rh)
{
	{ lh > rh };
};

template<class T, class O>
concept TComparable_GreaterEquals = requires(T lh, O rh)
{
	{ lh >= rh };
};

#pragma warning(push)
#pragma warning(disable: 4305)
template<class T>
constexpr bool IsRealType = ((T)(1.0 + 0.1)) != ((T)1.0);
#pragma warning(pop)

template<class T>
concept TIsRealType = IsRealType<T>;

template<class T>
concept TIsMatrixType = requires(T Arg, const T ConstArg)
{
	{ ConstArg.GetComponentOrDefault(0) };
	{ (bool)ConstArg.Contains(0) };
	{ (bool)ConstArg.Contains(0, 0) };
	{ (float)ConstArg[0] };
	{ (float)ConstArg[0][0] };
	{ (size_t)ConstArg.Rows };
	{ (size_t)ConstArg.Columns };
	{ (size_t)ConstArg.Count };
};

template<class T>
concept TIsObject = requires(SObject* Base, T* Derived)
{
	{ Base = Derived };
};
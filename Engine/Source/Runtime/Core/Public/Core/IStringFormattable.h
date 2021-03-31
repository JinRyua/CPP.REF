// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Object.h"

template<class T>
struct TIsFormattableStringConvertibleType
{
	template<class O> requires requires(const O& arg)
	{
		{ arg.ToString(nullptr) };
	}
	constexpr bool IsImpl(const T& arg)
	{
		arg.ToString(nullptr);
		return true;
	}
};

template<class T>
concept TIsFormattableStringConvertible = requires(const T& arg)
{
	{ arg.ToString() };
	{ arg.ToString(nullptr) };
};

interface IStringFormattable : virtual public SObject
{
	using SObject::ToString;

	virtual SString* ToString(SString* formatText) const = 0;
};
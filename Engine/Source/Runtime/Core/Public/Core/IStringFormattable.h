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

/// <summary>
/// 서식이 지정된 텍스트 형식을 가져올 수 있는 개체에 대한 공통 인터페이스를 제공합니다.
/// </summary>
interface IStringFormattable : virtual public SObject
{
	using SObject::ToString;

	/// <summary>
	/// 서식을 지정하여 간단한 텍스트 정보를 가져옵니다.
	/// </summary>
	/// <param name="formatText"> 서식 문자열을 전달합니다. </param>
	/// <returns> 생성된 텍스트 개체가 반환됩니다. </returns>
	virtual SString* ToString(SString* formatText) const = 0;
};
﻿// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Object.h"

#include <typeinfo>
#include <functional>
#include "String.h"
#include "Delegates/TFunction.h"

/// <summary>
/// 개체의 형식에 관한 리플렉션을 지원합니다.
/// </summary>
SCLASS(SType) class CORE_API SType : virtual public SObject
{
	SCLASS_BODY(SType)

	friend class TypeCollection;

private:
	const char* className;
	size_t hashCode;
	size_t rttiType;
	std::function<SObject*()> activator;
	size_t propertyCount;

	SPROPERTY(SString*, classNameObj);

public:
	SType();
	~SType() override;

	/// <summary>
	/// 형식의 간단한 이름을 문자열로 가져옵니다.
	/// </summary>
	/// <returns> 문자열 개체가 반환됩니다. </returns>
	SString* ToString() const override;

	/// <summary>
	/// 형식의 해시 코드 값을 가져옵니다.
	/// </summary>
	/// <returns> 해시 코드 값이 반환됩니다. </returns>
	size_t GetHashCode() const override;

	/// <summary>
	/// 형식의 RTTI 해시 코드 값을 가져옵니다.
	/// </summary>
	/// <returns> 해시 코드 값이 반환됩니다. </returns>
	size_t GetRTTIHashCode() const;

	/// <summary>
	/// 형식의 간단한 이름을 문자열로 가져옵니다.
	/// </summary>
	/// <returns> 가공되지 않은 문자열이 반환됩니다. </returns>
	const char* GetNativeString() const;

	/// <summary>
	/// 프로퍼티 개수를 가져옵니다.
	/// </summary>
	/// <returns> 개수가 반환됩니다. </returns>
	size_t GetPropertyCount() const;

	/// <summary>
	/// 형식 정보를 기반으로 개체를 생성합니다.
	/// </summary>
	/// <returns> 생성된 개체가 반환됩니다. </returns>
	SObject* Activate();

	static void* operator new(size_t length);
};
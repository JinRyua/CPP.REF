// Copyright 2017 CLOVERGAMES Co., Ltd. All right reserved.

#pragma once

#include "Core/Object.h"

#include <optional>

/// <summary>
/// 개체의 형식에 포함된 필드 리플렉션을 지원합니다.
/// </summary>
class CORE_API SField : virtual public SObject
{
	SCLASS_BODY(SField)

	friend class SType;

private:
	SType* parent;
	const char* fieldName;
	ssize_t fieldToType;
	size_t rttiType;
	std::function<SObject*(void*)> typeToObject;
	std::function<void*(SObject*)> objectToType;

	mutable SType* cachedFieldType;

private:
	SField();

public:
	~SField() override;

	/// <summary>
	/// 필드의 형식을 가져옵니다. 네이티브 자료형의 경우 null이 반환됩니다.
	/// </summary>
	/// <returns> 형식 개체가 반환됩니다. </returns>
	SType* GetFieldType() const;
	
	/// <summary>
	/// 필드의 이름을 가져옵니다.
	/// </summary>
	/// <returns> 문자열 개체가 반환됩니다. </returns>
	SString* GetFieldName() const;

	/// <summary>
	/// 인스턴스의 필드 값을 설정합니다. 네이티브 자료형의 경우 예외가 발생합니다.
	/// </summary>
	/// <param name="instance"> 인스턴스를 전달합니다. </param>
	/// <param name="value"> 필드 값을 전달합니다. </param>
	void SetValue(SObject* instance, SObject* value);

	/// <summary>
	/// 인스턴스의 필드 값을 가져옵니다. 네이티브 자료형의 경우 예외가 발생합니다.
	/// </summary>
	/// <param name="instance"> 인스턴스를 전달합니다. </param>
	/// <returns> 필드 값이 반환됩니다. </returns>
	SObject* GetValue(SObject* instance) const;

	static void* operator new(size_t length);

private:
	SType* GetCachedType() const;
};
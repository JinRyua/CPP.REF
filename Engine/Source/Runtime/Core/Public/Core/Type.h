// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Object.h"

#include <typeinfo>
#include <functional>
#include "Reflection/TypeCollection.h"

class SField;
class SString;

/// <summary>
/// 개체의 형식에 관한 리플렉션을 지원합니다.
/// </summary>
class CORE_API SType : virtual public SObject
{
	SCLASS_BODY(SType)

	friend class TypeCollection;
	friend class SField;

private:
	size_t hashCode;
	const char* className;
	std::function<SObject*(void*)> typeToObject;
	std::function<void*(SObject*)> objectToType;
	std::vector<Reflection::SPropertyMemberDeclare> memberDeclares;
	std::function<SObject*()> activator;
	size_t superRtti;

	std::vector<SField*> fields;

private:
	SType();

public:
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

	/// <summary>
	/// 이 클래스의 상위 클래스를 가져옵니다.
	/// </summary>
	/// <returns> 상위 클래스 형식이 반환됩니다. </returns>
	SType* GetSuper() const;

	/// <summary>
	/// 형식에 정의된 필드를 가져옵니다.
	/// </summary>
	/// <param name="name"> 필드 이름을 전달합니다. </param>
	/// <returns> 형식 개체가 반환됩니다. </returns>
	SField* GetField(const char* name);

	/// <summary>
	/// 형식에 정의된 필드를 가져옵니다.
	/// </summary>
	/// <param name="name"> 필드 이름을 전달합니다. </param>
	/// <returns> 형식 개체가 반환됩니다. </returns>
	SField* GetField(SString* name);

	static void* operator new(size_t length);

private:
	void RegisterFields();
};
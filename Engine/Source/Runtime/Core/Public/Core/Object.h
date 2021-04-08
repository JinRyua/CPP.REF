// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "CoreConcepts.h"
#include "WeakReferences.h"
#include "Reflection/ReflectionMacros.h"

class SObject;
class SString;
class SType;

template<TIsNotPointer T, bool bThreadSafe>
class TRefPtr;
template<TIsNotPointer T, bool bThreadSafe>
class TWeakPtr;

namespace Reflection
{
	struct PropertyRegisterBase;
}

/// <summary>
/// 리플렉션 가능한 모든 클래스에 대한 공통 함수를 제공합니다.
/// </summary>
class CORE_API SObject
{
public:
	using This = SObject;
	friend class TypeCollection;

	SCLASS_BODY(SObject);

private:
	template<TIsNotPointer T, bool bThreadSafe>
	friend class TRefPtr;
	template<TIsNotPointer T, bool bThreadSafe>
	friend class TWeakPtr;
		
	SObject(const SObject&) = delete;
	SObject(SObject&&) = delete;
	SObject& operator =(const SObject&) = delete;
	SObject& operator =(SObject&&) = delete;

private:
#if WITH_DEBUG
	static size_t ObjCount;
#endif

	bool bLockCollecting : 1;
	bool bReferenceCollectiong : 1;
	size_t ref_count;
	mutable WeakReferences* weak_references;

public:
	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	SObject();
	virtual ~SObject();

	/// <summary>
	/// 개체의 간단한 정보를 텍스트 형식으로 가져옵니다.
	/// </summary>
	/// <returns> 문자열 개체가 반환됩니다. </returns>
	virtual SString* ToString() const;
	
	/// <summary>
	/// 개체가 지정한 비교 연산을 사용합니다.
	/// </summary>
	/// <param name="right"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	virtual bool Equals(SObject* right) const;

	/// <summary>
	/// 개체의 단순 해시 값을 가져옵니다.
	/// </summary>
	/// <returns> 해시 값이 반환됩니다. </returns>
	virtual size_t GetHashCode() const;

	/// <summary>
	/// 개체의 형식 개체를 가져옵니다.
	/// </summary>
	/// <returns> 형식 개체가 반환됩니다. </returns>
	SType* GetType() const;

	/// <summary>
	/// 대상 형식으로 캐스트합니다.
	/// </summary>
	/// <param name="ptr"> 참조 포인터를 전달합니다. </param>
	/// <returns> 대상 형식으로 변경된 포인터가 반환됩니다. </returns>
	template<TIsNotPointer O, TIsNotPointer T, bool bThreadSafe> requires TIsBaseOf<O, SObject> && TIsBaseOf<T, SObject>
	inline static TRefPtr<O, bThreadSafe> Cast(TRefPtr<T, bThreadSafe> ptr);

	/// <summary>
	/// 대상 형식으로 캐스트합니다.
	/// </summary>
	/// <param name="ptr"> 포인터를 전달합니다. </param>
	/// <returns> 대상 형식으로 변경된 포인터가 반환됩니다. </returns>
	template<TIsNotPointer O, TIsNotPointer T> requires TIsBaseOf<O, SObject> && TIsBaseOf<T, SObject>
	inline static O* Cast(T* ptr);

	/// <summary>
	/// 대상 형식으로 캐스트합니다.
	/// </summary>
	/// <param name="ptr"> 포인터를 전달합니다. </param>
	/// <returns> 대상 형식으로 변경된 포인터가 반환됩니다. </returns>
	template<TIsNotPointer O, TIsNotPointer T> requires TIsBaseOf<O, SObject> && TIsBaseOf<T, SObject>
	inline static const O* Cast(const T* ptr);

	bool operator ==(SObject* right) const;
	bool operator !=(SObject* right) const;

private:
	/// <summary>
	/// 개체의 참조 횟수를 1회 증가시킵니다.
	/// </summary>
	void AddRef();

	/// <summary>
	/// 개체의 참조 횟수를 1회 감소시킵니다.
	/// </summary>
	void Release();

	/// <summary>
	/// 개체의 참조 횟수를 1회 증가시킵니다.
	/// </summary>
	void AddRefInterlocked();

	/// <summary>
	/// 개체의 참조 횟수를 1회 감소시킵니다.
	/// </summary>
	void ReleaseInterlocked();

	/// <summary>
	/// 개체의 약한 참조를 가져옵니다.
	/// </summary>
	/// <returns> 약한 참조 개체가 반환됩니다. </returns>
	WeakReferences* GetWeakReferences() const;

public:
	/// <summary>
	/// 개체의 현재 참조 횟수를 가져옵니다.
	/// </summary>
	/// <returns> 참조 횟수가 반환됩니다. </returns>
	size_t GetReferenceCount() const;

#if WITH_DEBUG
	static size_t GetObjectCount();
#endif

protected:
	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="bNoReferenceCollect"> 레퍼런스 수집기 지정 여부입니다. </param>
	SObject(bool bNoReferenceCollect);

private:
	constexpr static auto SPROPERTY_GetPropertyCount()
	{
		return 0;
	}
};

#include "Object.inl"
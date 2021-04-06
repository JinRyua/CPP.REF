// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Vector3.h"
#include "Core/CoreConcepts.h"

#pragma pack(push, 4)
/// <summary>
/// 평면을 나타냅니다.
/// </summary>
struct CORE_API Plane : public TNumericsBasicOperator<Plane, Vector3, float>
{
	/// <summary>
	/// 평면의 방향을 나타냅니다.
	/// </summary>
	Vector3 Normal;

	/// <summary>
	/// 평면의 방향으로 0위치에서의 거리를 나타냅니다.
	/// </summary>
	float Distance;

public:
	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Plane();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="inNormal"> 방향을 전달합니다. </param>
	/// <param name="inDistance"> 방향으로 0위치에서의 거리를 전달합니다. </param>
	Plane(const Vector3& inNormal, float inDistance);

	/// <summary>
	/// 대상 평면와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Plane& rh) const;

	/// <summary>
	/// 대상 평면와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Plane& rh, float epsilon) const;

	/// <summary>
	/// 해시 코드 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	size_t GetHashCode() const;

	/// <summary>
	/// 개체의 간단한 설명을 텍스트 형식으로 가져옵니다.
	/// </summary>
	/// <returns> 텍스트 개체가 반환됩니다. </returns>
	SString* ToString() const;

	/// <summary>
	/// 컴포넌트 값을 가져옵니다.
	/// </summary>
	/// <param name="index"> 컴포넌트 위치를 전달합니다. </param>
	/// <returns> 값이 반환됩니다. </returns>
	float GetComponentOrDefault(size_t index) const;

	/// <summary>
	/// 벡터 형식에서 값을 생성합니다.
	/// </summary>
	/// <param name="vector"> 벡터 형식의 값을 전달합니다. </param>
	template<TIsVectorType T>
	inline void Construct(const T& vector);

	/// <summary>
	/// 벡터 형식으로 변환합니다.
	/// </summary>
	/// <returns> 변환된 벡터 형식 값이 반환됩니다. </returns>
	template<TIsVectorType T>
	inline T Cast() const;

	/// <summary>
	/// 해당 인덱스가 포함되어 있는지 검사합니다.
	/// </summary>
	/// <param name="index"> 인덱스를 전달합니다. </param>
	/// <returns> 검사 결과가 반환됩니다. </returns>
	bool Contains(size_t index) const;

	/// <summary>
	/// 컴포넌트 개수를 가져옵니다.
	/// </summary>
	/// <returns> 개수가 반환됩니다. </returns>
	size_t GetCount() const { return 4; }

	/// <summary>
	/// 정규화된 평면 개체를 가져옵니다.
	/// </summary>
	/// <returns> 평면 개체가 반환됩니다. </returns>
	Plane GetNormalized() const;

	const float& operator [](size_t index) const;
	float& operator [](size_t index);

	/// <summary>
	/// 평면과 벡터의 내적 연산을 계산합니다.
	/// </summary>
	/// <param name="inPlane"> 평면을 전달합니다. </param>
	/// <param name="inVector"> 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float DotCoord(const Plane& inPlane, const Vector3& inVector);
};
#pragma pack(pop)

#include "Plane.inl"
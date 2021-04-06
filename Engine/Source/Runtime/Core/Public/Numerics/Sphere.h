// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Vector3.h"

#pragma pack(push, 4)
/// <summary>
/// 구를 표현합니다.
/// </summary>
struct CORE_API Sphere : public TNumericsBasicOperator<Sphere, Vector3, float>
{
	using This = Sphere;

	/// <summary>
	/// 중앙 위치를 나타냅니다.
	/// </summary>
	Vector3 Center;

	/// <summary>
	/// 반지름을 나타냅니다.
	/// </summary>
	float Radius;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Sphere();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="center"> 중앙 위치를 전달합니다. </param>
	/// <param name="radius"> 반지름을 전달합니다. </param>
	Sphere(const Vector3& center, float radius);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="cx"> 중앙 위치의 X를 전달합니다. </param>
	/// <param name="cy"> 중앙 위치의 Y를 전달합니다. </param>
	/// <param name="cz"> 중앙 위치의 Z를 전달합니다. </param>
	/// <param name="radius"> 반지름을 전달합니다. </param>
	Sphere(float cx, float cy, float cz, float radius);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Sphere(const Sphere& copy);

	/// <summary>
	/// 대상 구와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Sphere& rh) const;

	/// <summary>
	/// 대상 구와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Sphere& rh, float epsilon) const;

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
};
#pragma pack(pop)
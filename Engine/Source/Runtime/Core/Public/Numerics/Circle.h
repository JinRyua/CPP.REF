// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Vector2.h"

class SString;

#pragma pack(push, 4)
/// <summary>
/// 원을 표현합니다.
/// </summary>
struct CORE_API Circle : public TNumericsBasicOperator<Circle, Vector2, float>
{
	using This = Circle;

	/// <summary>
	/// 중앙 위치를 나타냅니다.
	/// </summary>
	Vector2 Center;

	/// <summary>
	/// 반지름을 나타냅니다.
	/// </summary>
	float Radius;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Circle();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="center"> 중앙 위치를 전달합니다. </param>
	/// <param name="radius"> 반지름을 전달합니다. </param>
	Circle(const Vector2& center, float radius);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="cx"> 중앙 위치의 X 값을 전달합니다. </param>
	/// <param name="cy"> 중앙 위치의 Y 값을 전달합니다. </param>
	/// <param name="radius"> 반지름을 전달합니다. </param>
	Circle(float cx, float cy, float radius);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Circle(const Circle& copy);

	/// <summary>
	/// 대상 원과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Circle& rh) const;

	/// <summary>
	/// 대상 원과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Circle& rh, float epsilon) const;

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
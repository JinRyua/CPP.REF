// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Vector2.h"

#pragma pack(push, 4)
/// <summary>
/// 사각형을 표현합니다.
/// </summary>
struct CORE_API Rect : public TNumericsBasicOperator<Rect, Vector2, Vector2>
{
	/// <summary>
	/// 시작 위치를 나타냅니다.
	/// </summary>
	Vector2 Min;

	/// <summary>
	/// 종료 위치를 나타냅니다.
	/// </summary>
	Vector2 Max;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Rect();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="min"> 시작 위치를 전달합니다. </param>
	/// <param name="max"> 종료 위치를 전달합니다. </param>
	Rect(const Vector2& min, const Vector2& max);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Rect(const Rect& copy);

	/// <summary>
	/// 대상 사각형과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Rect& rh) const;

	/// <summary>
	/// 대상 사각형과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Rect& rh, float epsilon) const;

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
	/// 중앙 위치를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector2 GetCenter() const;

	/// <summary>
	/// 사각형의 너비를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetWidth() const;

	/// <summary>
	/// 사각형의 높이를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetHeight() const;

	/// <summary>
	/// 사각형의 범위를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector2 GetExtent() const;

	/// <summary>
	/// 사각형의 크기를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetSize() const;
};
#pragma pack(pop)
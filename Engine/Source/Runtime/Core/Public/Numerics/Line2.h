// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Vector2.h"

struct Ray2;
class SString;

#pragma pack(push, 4)
/// <summary>
/// 선분을 표현합니다.
/// </summary>
struct CORE_API Line2 : public TNumericsBasicOperator<Line2, Vector2, Vector2>
{
	using This = Line2;

	/// <summary>
	/// 시작 위치를 나타냅니다.
	/// </summary>
	Vector2 Start;

	/// <summary>
	/// 종료 위치를 나타냅니다.
	/// </summary>
	Vector2 End;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Line2();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="start"> 시작 위치를 전달합니다. </param>
	/// <param name="end"> 종료 위치를 전달합니다. </param>
	Line2(const Vector2& start, const Vector2& end);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Line2(const Line2& copy);

	/// <summary>
	/// 대상 선분과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Line2& rh) const;

	/// <summary>
	/// 대상 선분과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Line2& rh, float epsilon) const;

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
	/// 시작 위치와 종료 위치 사이의 벡터 값을 가져옵니다.
	/// </summary>
	/// <param name="factor"> 0에서 1사이의 값을 전달합니다. </param>
	/// <returns> 벡터값이 반환됩니다. </returns>
	Vector2 GetPoint(float factor) const;

	/// <summary>
	/// 선분의 진행 방향과 길이를 가져옵니다.
	/// </summary>
	/// <returns> 벡터값이 반환됩니다. </returns>
	Vector2 GetVector() const;

	/// <summary>
	/// 광선 정보로부터 선분 개체를 생성합니다.
	/// </summary>
	/// <param name="ray"> 광선 정보를 전달합니다. </param>
	/// <returns> 선분 개체가 반환됩니다. </returns>
	static Line2 FromRay(const Ray2& ray);
};
#pragma pack(pop)
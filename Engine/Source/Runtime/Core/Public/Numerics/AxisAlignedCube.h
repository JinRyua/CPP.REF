// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include <optional>
#include "Vector3.h"

struct Ray3;
class SString;

#pragma pack(push, 4)
/// <summary>
/// 축 정렬 상자를 표현합니다.
/// </summary>
struct CORE_API AxisAlignedCube : public TNumericsBasicOperator<AxisAlignedCube, Vector3, Vector3>
{
	using This = AxisAlignedCube;

	/// <summary>
	/// 상자의 최소 위치를 나타냅니다.
	/// </summary>
	Vector3 Min;

	/// <summary>
	/// 상자의 최대 위치를 나타냅니다.
	/// </summary>
	Vector3 Max;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	AxisAlignedCube();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="min"> 최소 위치를 전달합니다. </param>
	/// <param name="max"> 최대 위치를 전달합니다. </param>
	AxisAlignedCube(const Vector3& min, const Vector3& max);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	AxisAlignedCube(const AxisAlignedCube& copy);

	/// <summary>
	/// 대상 축 정렬 상자와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const AxisAlignedCube& rh) const;

	/// <summary>
	/// 대상 축 정렬 상자와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const AxisAlignedCube& rh, float epsilon) const;

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
	/// 축 정렬 상자에서 꼭지점 위치를 가져옵니다.
	/// </summary>
	/// <param name="index"> 꼭지점 번호를 전달합니다. </param>
	/// <returns> 꼭지점 위치가 반환됩니다. </returns>
	Vector3 GetPoint(size_t index) const;

	/// <summary>
	/// 축 정렬 상자의 중앙 위치를 가져옵니다.
	/// </summary>
	/// <returns> 위치가 반환됩니다. </returns>
	Vector3 GetCenter() const;
};
#pragma pack(pop)
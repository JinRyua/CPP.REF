// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include <optional>
#include "Vector3.h"

#pragma warning(disable: 4251)
#pragma pack(push, 4)
/// <summary>
/// 3차원 광선 정보를 표현합니다.
/// </summary>
struct CORE_API Ray3 : public TNumericsBasicOperator<Ray3, Vector3, Vector3, std::optional<float>>
{
	/// <summary>
	/// 시작 위치를 나타냅니다.
	/// </summary>
	Vector3 Origin;

	/// <summary>
	/// 방향을 나타냅니다.
	/// </summary>
	Vector3 Direction;

	/// <summary>
	/// 진행 거리를 나타냅니다.
	/// </summary>
	std::optional<float> Distance;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Ray3();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="origin"> 시작 위치를 전달합니다. </param>
	/// <param name="direction"> 방향을 전달합니다. </param>
	/// <param name="distance"> 진행 거리를 전달합니다. </param>
	Ray3(const Vector3& origin, const Vector3& direction, std::optional<float> distance = std::nullopt);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기 값을 전달합니다. </param>
	Ray3(const Ray3& copy);

	/// <summary>
	/// 대상 광선과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Ray3& rh) const;

	/// <summary>
	/// 대상 광선과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Ray3& rh, float epsilon) const;

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
	/// 진행 거리만큼 이동한 벡터를 계산합니다.
	/// </summary>
	/// <param name="distance"> 진행 거리를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	Vector3 GetPoint(float distance) const;

	/// <summary>
	/// 진행 거리만큼 이동한 벡터를 계산합니다.
	/// </summary>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	Vector3 GetEndPoint() const;
};
#pragma pack(pop)
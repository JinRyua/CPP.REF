// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include <array>
#include "Vector3.h"
#include "Quaternion.h"

#pragma pack(push, 4)
/// <summary>
/// 회전을 가지는 상자를 표현합니다.
/// </summary>
struct CORE_API ObjectOrientedCube : public TNumericsBasicOperator<ObjectOrientedCube, Vector3, Vector3, Quaternion>
{
	using This = ObjectOrientedCube;

	/// <summary>
	/// 중앙 위치를 나타냅니다.
	/// </summary>
	Vector3 Center;
	
	/// <summary>
	/// 확장 크기를 나타냅니다.
	/// </summary>
	Vector3 Extent;

	/// <summary>
	/// 회전 사원수를 나타냅니다.
	/// </summary>
	Quaternion Rotation;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	ObjectOrientedCube();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="center"> 중앙 위치를 전달합니다. </param>
	/// <param name="extent"> 확장 크기를 전달합니다. </param>
	/// <param name="rotation"> 회전 사원수를 전달합니다. </param>
	ObjectOrientedCube(const Vector3& center, const Vector3& extent, const Quaternion& rotation);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	ObjectOrientedCube(const ObjectOrientedCube& copy);

	/// <summary>
	/// 대상 상자와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const ObjectOrientedCube& rh) const;

	/// <summary>
	/// 대상 상자와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const ObjectOrientedCube& rh, float epsilon) const;

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
	/// 상자의 8방향 위치 벡터를 계산합니다.
	/// </summary>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	std::array<Vector3, 8> CalcVertices() const;

	/// <summary>
	/// X축 벡터를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetAxisX() const;

	/// <summary>
	/// Y축 벡터를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetAxisY() const;

	/// <summary>
	/// Z축 벡터를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetAxisZ() const;
};
#pragma pack(pop)
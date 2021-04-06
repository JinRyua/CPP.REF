// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Plane.h"

struct Matrix4x4;

/// <summary>
/// 프러스텀을 표현합니다.
/// </summary>
struct CORE_API Frustum : public TNumericsBasicOperator<Frustum, Plane, Plane, Plane, Plane, Plane, Plane>
{
	/// <summary>
	/// 프러스텀을 정의하는 6개의 평면을 나타냅니다.
	/// </summary>
	Plane Planes[6];

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Frustum();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="left"> 왼쪽 평면을 전달합니다. </param>
	/// <param name="top"> 위쪽 평면을 전달합니다. </param>
	/// <param name="right"> 오른쪽 평면을 전달합니다. </param>
	/// <param name="bottom"> 아래쪽 평면을 전달합니다. </param>
	/// <param name="near"> 가까운 쪽 평면을 전달합니다. </param>
	/// <param name="far"> 먼 쪽 평면을 전달합니다. </param>
	Frustum(const Plane& left, const Plane& top, const Plane& right, const Plane& bottom, const Plane& near, const Plane& far);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="planes"> 6개의 평면 배열을 전달합니다. </param>
	Frustum(const Plane* planes);

	/// <summary>
	/// 왼쪽 평면을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Plane GetLeft() { return Planes[0]; }

	/// <summary>
	/// 위쪽 평면을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Plane GetTop() { return Planes[1]; }

	/// <summary>
	/// 오른쪽 평면을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Plane GetRight() { return Planes[2]; }

	/// <summary>
	/// 아래쪽 평면을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Plane GetBottom() { return Planes[3]; }

	/// <summary>
	/// 가까운 쪽 평면을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Plane GetNear() { return Planes[4]; }

	/// <summary>
	/// 먼 쪽 평면을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Plane GetFar() { return Planes[5]; }

	/// <summary>
	/// 뷰 행렬을 이용하여 프러스텀을 생성합니다.
	/// </summary>
	/// <param name="inViewProj"> 뷰 행렬을 전달합니다. </param>
	/// <returns> 개체가 반환됩니다. </returns>
	static Frustum Construct(const Matrix4x4& inViewProj);
};
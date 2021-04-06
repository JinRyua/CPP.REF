// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

struct Frustum;
struct Vector3;
struct Sphere;
struct AxisAlignedCube;

/// <summary>
/// 엔진 기초 타입의 겹침 테스트를 수행합니다.
/// </summary>
class CORE_API OverlapTest abstract final
{
	OverlapTest() = delete;

public:
	/// <summary>
	/// <see cref="Frustum"/> 형식과 <see cref="Vector"/> 형식의 겹침 테스트를 진행합니다.
	/// </summary>
	/// <param name="inFrustum"> 개체를 전달합니다. </param>
	/// <param name="inVector"> 개체를 전달합니다. </param>
	/// <returns> 겹침 결과가 반환됩니다. 겹칠 경우 <see langword="true"/>가 반환됩니다. </returns>
	static bool IsOverlap(const Frustum& inFrustum, const Vector3& inVector);

	/// <summary>
	/// <see cref="Frustum"/> 형식과 <see cref="Vector"/> 형식의 겹침 테스트를 진행합니다.
	/// </summary>
	/// <param name="inVector"> 개체를 전달합니다. </param>
	/// <param name="inFrustum"> 개체를 전달합니다. </param>
	/// <returns> 겹침 결과가 반환됩니다. 겹칠 경우 <see langword="true"/>가 반환됩니다. </returns>
	static bool IsOverlap(const Vector3& inVector, const Frustum& inFrustum) { return IsOverlap(inFrustum, inVector); }

	/// <summary>
	/// <see cref="Frustum"/> 형식과 <see cref="Sphere"/> 형식의 겹침 테스트를 진행합니다.
	/// </summary>
	/// <param name="inFrustum"> 개체를 전달합니다. </param>
	/// <param name="inSphere"> 개체를 전달합니다. </param>
	/// <returns> 겹침 결과가 반환됩니다. 겹칠 경우 <see langword="true"/>가 반환됩니다. </returns>
	static bool IsOverlap(const Frustum& inFrustum, const Sphere& inSphere);

	/// <summary>
	/// <see cref="Frustum"/> 형식과 <see cref="Sphere"/> 형식의 겹침 테스트를 진행합니다.
	/// </summary>
	/// <param name="inSphere"> 개체를 전달합니다. </param>
	/// <param name="inFrustum"> 개체를 전달합니다. </param>
	/// <returns> 겹침 결과가 반환됩니다. 겹칠 경우 <see langword="true"/>가 반환됩니다. </returns>
	static bool IsOverlap(const Sphere& inSphere, const Frustum& inFrustum) { return IsOverlap(inFrustum, inSphere); }

	/// <summary>
	/// <see cref="Frustum"/> 형식과 <see cref="AxisAlignedCube"/> 형식의 겹침 테스트를 진행합니다.
	/// </summary>
	/// <param name="inFrustum"> 개체를 전달합니다. </param>
	/// <param name="inAABB"> 개체를 전달합니다. </param>
	/// <returns> 겹침 결과가 반환됩니다. 겹칠 경우 <see langword="true"/>가 반환됩니다. </returns>
	static bool IsOverlap(const Frustum& inFrustum, const AxisAlignedCube& inAABB);

	/// <summary>
	/// <see cref="Frustum"/> 형식과 <see cref="AxisAlignedCube"/> 형식의 겹침 테스트를 진행합니다.
	/// </summary>
	/// <param name="inAABB"> 개체를 전달합니다. </param>
	/// <param name="inFrustum"> 개체를 전달합니다. </param>
	/// <returns> 겹침 결과가 반환됩니다. 겹칠 경우 <see langword="true"/>가 반환됩니다. </returns>
	static bool IsOverlap(const AxisAlignedCube& inAABB, const Frustum& inFrustum) { return IsOverlap(inFrustum, inAABB); }
};
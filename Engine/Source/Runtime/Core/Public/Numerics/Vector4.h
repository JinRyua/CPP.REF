// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Core/CoreConcepts.h"

struct Vector3;

#pragma pack(push, 4)
/// <summary>
/// 3차원 벡터를 표현합니다.
/// </summary>
struct CORE_API Vector4 : public TNumericsBasicOperator<Vector4, float, float, float, float>
{
	using This = Vector4;

	/// <summary>
	/// X값을 나타냅니다.
	/// </summary>
	float X;

	/// <summary>
	/// Y값을 나타냅니다.
	/// </summary>
	float Y;

	/// <summary>
	/// Z값을 나타냅니다.
	/// </summary>
	float Z;

	/// <summary>
	/// W값을 나타냅니다.
	/// </summary>
	float W;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Vector4();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="v3"> XYZ값을 채울 3차원 벡터를 전달합니다. </param>
	/// <param name="w"> W값을 전달합니다. </param>
	Vector4(const Vector3& v3, float w);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="x"> X값을 전달합니다. </param>
	/// <param name="y"> Y값을 전달합니다. </param>
	/// <param name="z"> Z값을 전달합니다. </param>
	/// <param name="w"> W값을 전달합니다. </param>
	Vector4(float x, float y, float z, float w);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="splat"> 단일 값을 전달합니다. </param>
	Vector4(float splat);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Vector4(const Vector4& copy);

	/// <summary>
	/// 대상 개체와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Vector4& rh) const;

	/// <summary>
	/// 대상 개체와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Vector4& rh, float epsilon) const;

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
	/// 최대 길이로 한정된 벡터를 가져옵니다.
	/// </summary>
	/// <param name="inMaxLength"> 최대 길이를 전달합니다. </param>
	/// <returns> 값이 반환됩니다. </returns>
	Vector4 GetClampedToMaxLength(float inMaxLength) const;

	/// <summary>
	/// 제곱 길이를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetLengthSq() const;

	/// <summary>
	/// 길이를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetLength() const;

	/// <summary>
	/// 정규화된 벡터를 계산합니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector4 GetNormalized() const;

	/// <summary>
	/// 방향 벡터를 계산합니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector4 GetDirection() const;

	/// <summary>
	/// 방향을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetDirection(const Vector4& value);

	const float& operator [](size_t index) const;
	float& operator [](size_t index);

	Vector4 operator -() const;
	Vector4 operator +(const Vector4& right) const;
	Vector4 operator -(const Vector4& right) const;
	Vector4 operator *(const Vector4& right) const;
	Vector4 operator /(const Vector4& right) const;
	float operator |(const Vector4& right) const;

	Vector4& operator +=(const Vector4& right);
	Vector4& operator -=(const Vector4& right);
	Vector4& operator *=(const Vector4& right);
	Vector4& operator /=(const Vector4& right);

	/// <summary>
	/// 두 벡터의 길이 제곱을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float DistanceSq(const Vector4& left, const Vector4& right);

	/// <summary>
	/// 두 벡터의 길이를 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float Distance(const Vector4& left, const Vector4& right);

	/// <summary>
	/// 두 벡터의 내적을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float DotProduct(const Vector4& left, const Vector4& right);

	/// <summary>
	/// 두 벡터의 최솟값을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Vector4 Min(const Vector4& left, const Vector4& right);

	/// <summary>
	/// 두 벡터의 최댓값을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Vector4 Max(const Vector4& left, const Vector4& right);

	/// <summary>
	/// 0값을 가져옵니다.
	/// </summary>
	static const Vector4 Zero;

	/// <summary>
	/// 1값을 가져옵니다.
	/// </summary>
	static const Vector4 One;
};
#pragma pack(pop)

CORE_API Vector4 operator +(float left, const Vector4& right);
CORE_API Vector4 operator -(float left, const Vector4& right);
CORE_API Vector4 operator *(float left, const Vector4& right);
CORE_API Vector4 operator /(float left, const Vector4& right);

#include "Vector4.inl"
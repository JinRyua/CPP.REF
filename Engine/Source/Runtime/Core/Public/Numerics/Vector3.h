// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Core/CoreConcepts.h"

struct AxisAlignedCube;
struct Vector2;

#pragma pack(push, 4)
/// <summary>
/// 3차원 벡터를 표현합니다.
/// </summary>
struct CORE_API Vector3 : public TNumericsBasicOperator<Vector3, float, float, float>
{
	using This = Vector3;

	class SelectControl
	{
		friend struct Vector3;

		char Value;

	public:
		inline constexpr SelectControl(bool v1, bool v2, bool v3);

		static constexpr SelectControl Less(const Vector3& lh, const Vector3& rh);
		static constexpr SelectControl Greater(const Vector3& lh, const Vector3& rh);
	};

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
	/// 개체를 초기화합니다.
	/// </summary>
	Vector3();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="v2"> XY값을 채울 2차원 벡터를 전달합니다. </param>
	/// <param name="z"> Z값을 전달합니다. </param>
	Vector3(const Vector2& v2, float z);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="x"> X값을 전달합니다. </param>
	/// <param name="y"> Y값을 전달합니다. </param>
	/// <param name="z"> Z값을 전달합니다. </param>
	Vector3(float x, float y, float z);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="splat"> 단일 값을 전달합니다. </param>
	Vector3(float splat);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Vector3(const Vector3& copy);

	/// <summary>
	/// 대상 개체와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Vector3& rh) const;

	/// <summary>
	/// 대상 개체와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Vector3& rh, float epsilon) const;

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
	size_t GetCount() const { return 3; }

	/// <summary>
	/// 최대 길이로 한정된 벡터를 가져옵니다.
	/// </summary>
	/// <param name="inMaxLength"> 최대 길이를 전달합니다. </param>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetClampedToMaxLength(float inMaxLength) const;

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
	Vector3 GetNormalized() const;

	/// <summary>
	/// 방향 벡터를 계산합니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetDirection() const;

	/// <summary>
	/// 방향을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetDirection(const Vector3& value);

	const float& operator [](size_t index) const;
	float& operator [](size_t index);

	Vector3 operator -() const;
	Vector3 operator +(const Vector3& right) const;
	Vector3 operator -(const Vector3& right) const;
	Vector3 operator *(const Vector3& right) const;
	Vector3 operator /(const Vector3& right) const;
	Vector3 operator ^(const Vector3& right) const;
	float operator |(const Vector3& right) const;

	Vector3& operator +=(const Vector3& right);
	Vector3& operator -=(const Vector3& right);
	Vector3& operator *=(const Vector3& right);
	Vector3& operator /=(const Vector3& right);
	Vector3& operator ^=(const Vector3& right);

	/// <summary>
	/// 두 벡터의 길이 제곱을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float DistanceSq(const Vector3& left, const Vector3& right);

	/// <summary>
	/// 두 벡터의 길이를 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float Distance(const Vector3& left, const Vector3& right);

	/// <summary>
	/// 두 벡터의 내적을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float DotProduct(const Vector3& left, const Vector3& right);

	/// <summary>
	/// 두 벡터의 외적을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Vector3 CrossProduct(const Vector3& left, const Vector3& right);

	/// <summary>
	/// 두 벡터의 최솟값을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Vector3 Min(const Vector3& left, const Vector3& right);

	/// <summary>
	/// 두 벡터의 최댓값을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Vector3 Max(const Vector3& left, const Vector3& right);

	/// <summary>
	/// 지정한 위치의 벡터 모음을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 벡터를 전달합니다. </param>
	/// <param name="right"> 두 번째 벡터를 전달합니다. </param>
	/// <param name="selectControl"> 선택할 벡터 위치를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Vector3 Select(const Vector3& left, const Vector3& right, const SelectControl& selectControl);

	/// <summary>
	/// 상향 벡터를 가져옵니다.
	/// </summary>
	static const Vector3 Up;

	/// <summary>
	/// 전방 벡터를 가져옵니다.
	/// </summary>
	static const Vector3 Forward;

	/// <summary>
	/// 우측 벡터를 가져옵니다.
	/// </summary>
	static const Vector3 Right;

	/// <summary>
	/// X축 벡터를 가져옵니다.
	/// </summary>
	static const Vector3 AxisX;

	/// <summary>
	/// Y축 벡터를 가져옵니다.
	/// </summary>
	static const Vector3 AxisY;

	/// <summary>
	/// Z축 벡터를 가져옵니다.
	/// </summary>
	static const Vector3 AxisZ;

	/// <summary>
	/// 0값을 가져옵니다.
	/// </summary>
	static const Vector3 Zero;

	/// <summary>
	/// 1값을 가져옵니다.
	/// </summary>
	static const Vector3 One;
};
#pragma pack(pop)

CORE_API Vector3 operator +(float left, const Vector3& right);
CORE_API Vector3 operator -(float left, const Vector3& right);
CORE_API Vector3 operator *(float left, const Vector3& right);
CORE_API Vector3 operator /(float left, const Vector3& right);

#include "Vector3.inl"
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include <utility>
#include "Mathematics/TAngleDef.h"

struct Vector3;
struct Vector4;
struct Matrix4x4;

#pragma pack(push, 4)
/// <summary>
/// 사원수를 표현합니다.
/// </summary>
struct CORE_API Quaternion : public TNumericsBasicOperator<Quaternion, float, float, float, float>
{
	/// <summary>
	/// X 구성요소를 나타냅니다.
	/// </summary>
	float X;
	
	/// <summary>
	/// Y 구성요소를 나타냅니다.
	/// </summary>
	float Y;

	/// <summary>
	/// Z 구성요소를 나타냅니다.
	/// </summary>
	float Z;

	/// <summary>
	/// W 구성요소를 나타냅니다.
	/// </summary>
	float W;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Quaternion();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="x"> X 구성요소를 전달합니다. </param>
	/// <param name="y"> Y 구성요소를 전달합니다. </param>
	/// <param name="z"> Z 구성요소를 전달합니다. </param>
	/// <param name="w"> W 구성요소를 전달합니다. </param>
	Quaternion(float x, float y, float z, float w);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="xyz"> XYZ 구성요소를 전달합니다. </param>
	/// <param name="w"> W 구성요소를 전달합니다. </param>
	Quaternion(const Vector3& xyz, float w);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="splat"> 단일 값을 전달합니다. </param>
	Quaternion(float splat);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Quaternion(const Quaternion& copy);

	/// <summary>
	/// 대상 사원수와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Quaternion& rh) const;

	/// <summary>
	/// 대상 사원수와 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Quaternion& rh, float epsilon) const;

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
	/// 벡터를 회전합니다.
	/// </summary>
	/// <param name="v"> 벡터를 전달합니다. </param>
    /// <param name="bCoord"> 위치 벡터인지 나타내는 값을 전달합니다. </param>
    /// <returns> 변환된 벡터가 반환됩니다. </returns>
	Vector3 RotateVector(const Vector3& v, bool bCoord = true) const;

	/// <summary>
	/// 벡터를 변환합니다.
	/// </summary>
	/// <param name="v"> 벡터를 전달합니다. </param>
	/// <returns> 변환된 벡터가 반환됩니다. </returns>
	Vector4 RotateVector(const Vector4& v) const;

	/// <summary>
	/// 벡터의 제곱 길이를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetLengthSq() const;

	/// <summary>
	/// 벡터의 길이를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetLength() const;

	/// <summary>
	/// 정규화된 값을 계산합니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Quaternion GetNormalized() const;

	/// <summary>
	/// 벡터 부분을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetVectorPart() const;

	/// <summary>
	/// 벡터 부분을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetVectorPart(const Vector3& value);

	/// <summary>
	/// 회전 각도를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	float GetAngle() const;

	/// <summary>
	/// 회전 각도를 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetAngle(float value);

	/// <summary>
	/// 회전 축을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Vector3 GetAxis() const;

	/// <summary>
	/// 회전 축을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetAxis(const Vector3& value);

	/// <summary>
	/// 사원수의 역을 계산합니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Quaternion GetInverse() const;

	/// <summary>
	/// 행렬로 변환합니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Matrix4x4 GetMatrix() const;

	const float& operator [](size_t index) const;
	float& operator [](size_t index);

	Quaternion operator -() const;
	Quaternion operator +(const Quaternion& right) const;
	Quaternion operator -(const Quaternion& right) const;
	Quaternion operator *(const Quaternion& right) const;
	Quaternion operator /(const Quaternion& right) const;
	float operator |(const Quaternion& right) const;

	Quaternion& operator +=(const Quaternion& right);
	Quaternion& operator -=(const Quaternion& right);
	Quaternion& operator *=(const Quaternion& right);
	Quaternion& operator /=(const Quaternion& right);

	/// <summary>
	/// 두 사원수의 내적을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 사원수를 전달합니다. </param>
	/// <param name="right"> 두 번째 사원수를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static float DotProduct(const Quaternion& left, const Quaternion& right);

	/// <summary>
	/// 축과 회전 각도로부터 사원수를 생성합니다.
	/// </summary>
	/// <param name="axis"> 축 벡터를 전달합니다. </param>
	/// <param name="angle"> 회전 각도를 전달합니다. </param>
	/// <returns> 개체가 반환됩니다. </returns>
	static Quaternion FromAxisAngle(const Vector3& axis, TDegrees<float> angle);

	/// <summary>
	/// 두 사원수의 회전 합을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 사원수를 전달합니다. </param>
	/// <param name="right"> 두 번째 사원수를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Quaternion Concatenate(const Quaternion& left, const Quaternion& right);

	/// <summary>
	/// 행렬로부터 회전 사원수를 생성합니다.
	/// </summary>
	/// <param name="rotationMatrix"> 회전 행렬을 전달합니다. </param>
	/// <returns> 개체가 반환됩니다. </returns>
	static Quaternion FromMatrix(const Matrix4x4& rotationMatrix);

	/// <summary>
	/// 오일러 각도를 지정하여 회전 사원수를 생성합니다.
	/// </summary>
	/// <param name="yaw"> Yaw 회전 각도를 전달합니다. </param>
	/// <param name="pitch"> Pitch 회전 각도를 전달합니다. </param>
	/// <param name="roll"> Roll 회전 각도를 전달합니다. </param>
	/// <returns> 개체가 반환됩니다. </returns>
	static Quaternion FromEuler(TDegrees<float> yaw, TDegrees<float> pitch, TDegrees<float> roll);

	/// <summary>
	/// 두 사원수의 사이 회전을 보간합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 사원수를 전달합니다. </param>
	/// <param name="right"> 두 번째 사원수를 전달합니다. </param>
	/// <param name="t"> 보간 계수를 전달합니다. </param>
	/// <returns> 보간 결과가 반환됩니다. </returns>
	static Quaternion Lerp(const Quaternion& left, const Quaternion& right, float t);

	/// <summary>
	/// 두 사원수의 사이 회전을 보간합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 사원수를 전달합니다. </param>
	/// <param name="right"> 두 번째 사원수를 전달합니다. </param>
	/// <param name="t"> 보간 계수를 전달합니다. </param>
	/// <returns> 보간 결과가 반환됩니다. </returns>
	static Quaternion Slerp(const Quaternion& left, const Quaternion& right, float t);
	
	/// <summary>
	/// 특정 방향을 바라보는 회전을 계산합니다.
	/// </summary>
	/// <param name="forward"> 바라보는 방향을 전달합니다. </param>
	/// <param name="up"> 상향 벡터를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	static Quaternion LookTo(const Vector3& forward, const Vector3& up);

	/// <summary>
	/// 단위 사원수를 가져옵니다.
	/// </summary>
	static Quaternion Identity;
};
#pragma pack(pop)

CORE_API Quaternion operator +(float left, const Quaternion& right);
CORE_API Quaternion operator -(float left, const Quaternion& right);
CORE_API Quaternion operator *(float left, const Quaternion& right);
CORE_API Quaternion operator /(float left, const Quaternion& right);

#include "Quaternion.inl"

// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

template<class T>
concept THasLerp = requires()
{
	{ T::Lerp(T(), T(), (float)0) };
};

template<class T>
constexpr bool VHasLerp = false;
template<THasLerp T>
constexpr bool VHasLerp<T> = true;

template<TIsRealType T>
struct TRadians;
template<TIsRealType T>
struct TDegrees;
struct Vector4;
struct Vector3;
struct Vector2;

template<class T>
concept TOverrideMinMax = requires()
{
	{ T::Min(T(), T()) };
	{ T::Max(T(), T()) };
};

class Math abstract final
{
private:
	static constexpr const size_t Primes[] =
	{
		3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
		1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591,
		17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
		187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
		1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369
	};

	static constexpr const int HashPrime = 101;
	static constexpr const int MaxPrimeArrayLength = 0x7FEFFFFD;

public:
	CORE_API static float Sin(TRadians<float> value);
	CORE_API static float Cos(TRadians<float> value);
	CORE_API static float Tan(TRadians<float> value);
	CORE_API static float Asin(float value);
	CORE_API static float Acos(float value);
	CORE_API static float Atan(float value);
	CORE_API static float Atan2(float y, float x);
	CORE_API static std::pair<float, float> SinCos(TRadians<float> value);
	CORE_API static float InvSqrt(float x);
	CORE_API static float Sqrt(float x);

	/// <summary>
	/// 최솟값을 넘는 소수를 가져옵니다.
	/// </summary>
	/// <param name="min"> 최솟값을 가져옵니다. </param>
	/// <returns> 일치하는 소수가 반환됩니다. </returns>
	CORE_API static size_t GetPrime(size_t min);

	/// <summary>
	/// 소수 단위로 확장합니다.
	/// </summary>
	/// <param name="oldSize"> 이전 크기를 전달합니다. </param>
	/// <returns> 일치하는 소수 값이 반환됩니다. </returns>
	CORE_API static size_t ExpandPrime(size_t oldSize);

	/// <summary>
	/// 전달된 값이 소수인지 검사합니다.
	/// </summary>
	/// <param name="candidate"> 값을 전달합니다. </param>
	/// <returns> 결과가 반환됩니다. </returns>
	CORE_API static bool IsPrime(size_t candidate);

	/// <summary>
	/// 왼쪽 값과 오른쪽 값 사이의 보간 값을 계산합니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <param name="left"> 왼쪽 값을 전달합니다. </param>
	/// <param name="right"> 오른쪽 값을 전달합니다. </param>
	/// <param name="t"> 보간 계수를 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	template<class T>
	inline static constexpr T Lerp(const T& left, const T& right, float t);

	/// <summary>
	/// 제곱 값을 계산합니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <param name="value"> 값을 전달합니다. </param>
	/// <returns> 계산 결과가 반환됩니다. </returns>
	template<class T>
	inline static constexpr T Square(const T& value);

	/// <summary>
	/// 값을 나눈 나머지를 계산합니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <param name="value"> 값을 전달합니다. </param>
	/// <param name="divisor"> 제수를 전달합니다. </param>
	/// <returns> 나머지 값이 반환됩니다. </returns>
	template<class T>
	inline static constexpr T Mod(const T& value, const T& divisor);

	/// <summary>
	/// 절댓값을 계산합니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <param name="value"> 값을 전달합니다. </param>
	/// <returns> 절댓값이 반환됩니다. </returns>
	template<class T>
	inline static constexpr T Abs(const T& value);

	/// <summary>
	/// 전달된 값 중 최솟값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <typeparam name="...TRest"> 값 형식을 전달합니다. </typeparam>
	/// <param name="lh"> 값 목록을 전달합니다. </param>
	/// <param name="rh"> 값 목록을 전달합니다. </param>
	/// <param name="...rhs"> 값 목록을 전달합니다. </param>
	/// <returns> 최솟값이 반환됩니다. </returns>
	template<class T, class... TRest>
	inline static constexpr T Min(const T& lh, const T& rh, TRest&&... rhs);

	/// <summary>
	/// 전달된 값 중 최솟값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <typeparam name="...TRest"> 값 형식을 전달합니다. </typeparam>
	/// <param name="lh"> 값 목록을 전달합니다. </param>
	/// <param name="rh"> 값 목록을 전달합니다. </param>
	/// <param name="...rhs"> 값 목록을 전달합니다. </param>
	/// <returns> 최솟값이 반환됩니다. </returns>
	template<TOverrideMinMax T, class... TRest>
	inline static constexpr T Min(const T& lh, const T& rh, TRest&&... rhs);

	/// <summary>
	/// 전달된 값 중 최댓값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <typeparam name="...TRest"> 값 형식을 전달합니다. </typeparam>
	/// <param name="lh"> 값 목록을 전달합니다. </param>
	/// <param name="rh"> 값 목록을 전달합니다. </param>
	/// <param name="...rhs"> 값 목록을 전달합니다. </param>
	/// <returns> 최댓값이 반환됩니다. </returns>
	template<class T, class... TRest>
	inline static constexpr T Max(const T& lh, const T& rh, TRest&&... rhs);

	/// <summary>
	/// 전달된 값 중 최댓값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <typeparam name="...TRest"> 값 형식을 전달합니다. </typeparam>
	/// <param name="lh"> 값 목록을 전달합니다. </param>
	/// <param name="rh"> 값 목록을 전달합니다. </param>
	/// <param name="...rhs"> 값 목록을 전달합니다. </param>
	/// <returns> 최댓값이 반환됩니다. </returns>
	template<TOverrideMinMax T, class... TRest>
	inline static constexpr T Max(const T& lh, const T& rh, TRest&&... rhs);

	/// <summary>
	/// 값을 하한값과 상한값으로 제한합니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <param name="value"> 값을 전달합니다. </param>
	/// <param name="start"> 하한값을 전달합니다. </param>
	/// <param name="end"> 상한값을 전달합니다. </param>
	/// <returns> 제한된 값이 반환됩니다. </returns>
	template<class T>
	inline static constexpr T Clamp(const T& value, const T& start, const T& end);

	/// <summary>
	/// 값이 지정한 범위 안에 존재하는지 검사합니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	/// <param name="value"> 값을 전달합니다. </param>
	/// <param name="start"> 시작 범위를 전달합니다. </param>
	/// <param name="end"> 종료 범위를 전달합니다. </param>
	/// <returns> 검사 결과가 반환됩니다. </returns>
	template<class T>
	inline static constexpr bool InRange(const T& value, const T& start, const T& end);

	/// <summary>
	/// PI 값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	template<class T = float>
	inline static constexpr const T PI = (T)3.141592;

	/// <summary>
	/// 반 PI 값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	template<class T = float>
	inline static constexpr const T HalfPI = PI<T> / (T)2;

	/// <summary>
	/// 역 PI 값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	template<class T = float>
	inline static constexpr const T InvPI = (T)1 / PI<T>;

	/// <summary>
	/// 두 배 PI 값을 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	template<class T = float>
	inline static constexpr const T PIx2 = PI<T> * (T)2.0;

	/// <summary>
	/// 임의의 작은 수를 가져옵니다.
	/// </summary>
	/// <typeparam name="T"> 값 형식을 전달합니다. </typeparam>
	template<class T = float>
	inline static constexpr const T SmallNumber = (T)1.e-6;
};

#include "Math.inl"
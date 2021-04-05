// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/String.h"

#include "Math.h"

template<TIsRealType T>
struct TRadians;

/// <summary>
/// 각도 단위를 래핑합니다.
/// </summary>
template<TIsRealType T = float>
struct TDegrees
{
private:
	static constexpr T PI = (T)3.141592;
	static constexpr T InvPI = PI / (T)180.0;
	static constexpr T AngleMax = (T)360.0;
	static constexpr T AngleHalf = (T)180.0;

public:
	T Value;

	/// <summary>
	/// 초기화되지 않은 개체를 가져옵니다.
	/// </summary>
	inline TDegrees()
	{

	}

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="value"> 초기화 값을 전달합니다. </param>
	inline constexpr TDegrees(const T& value) : Value(value)
	{

	}

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="value"> 초기화 값을 전달합니다. </param>
	inline constexpr TDegrees(const TDegrees& value) : Value(value.Value)
	{

	}

	/// <summary>
	/// 개체의 간단한 텍스트 설명을 가져옵니다.
	/// </summary>
	/// <returns> 텍스트 개체가 반환됩니다. </returns>
	inline SString* ToString() const
	{
		return SString::Format(L"{0}°", Value);
	}

	/// <summary>
	/// 각도 단위로 한정된 값을 가져옵니다.
	/// </summary>
	/// <returns> 한정된 값이 반환됩니다. </returns>
	inline constexpr TDegrees GetClamped() const;

	/// <summary>
	/// 각도 단위로 한정된 값을 가져옵니다.
	/// </summary>
	/// <returns> 한정된 값이 반환됩니다. </returns>
	inline constexpr TDegrees GetNormalized() const;

	/// <summary>
	/// 라디안 단위로 변환합니다.
	/// </summary>
	/// <returns> 변환된 라디안 값이 반환됩니다. </returns>
	template<TIsRealType O = T>
	inline constexpr TRadians<O> ToRadians() const;

	inline TDegrees& operator =(const TDegrees& value)
	{
		Value = value.Value;
		return *this;
	}

	inline TDegrees& operator +=(const TDegrees& value)
	{
		Value += value.Value;
		return *this;
	}

	inline TDegrees& operator -=(const TDegrees& value)
	{
		Value -= value.Value;
		return *this;
	}

	inline TDegrees& operator *=(const T& value)
	{
		Value *= value;
		return *this;
	}

	inline TDegrees& operator /=(const T& value)
	{
		Value /= value;
		return *this;
	}

	inline constexpr TDegrees operator -() const
	{
		return TDegrees(-Value);
	}

	inline constexpr TDegrees operator +(const TDegrees& value) const
	{
		return TDegrees(Value + value.Value);
	}

	inline constexpr TDegrees operator -(const TDegrees& value) const
	{
		return TDegrees(Value - value.Value);
	}

	inline constexpr TDegrees operator *(const T& value) const
	{
		return TDegrees(Value * value);
	}

	inline constexpr TDegrees operator /(const T& value) const
	{
		return TDegrees(Value / value);
	}

	template<TIsRealType O> requires TIsSmallThen<O, T>
	inline constexpr explicit operator TDegrees<O>() const
	{
		return TDegrees<O>(static_cast<O>(Value));
	}

	template<TIsRealType O> requires TIsGreaterEqualsThen<O, T>
	inline constexpr operator TDegrees<O>() const
	{
		return TDegrees<O>(static_cast<O>(Value));
	}

	template<TIsRealType O> requires TIsSmallThen<O, T>
	inline constexpr explicit operator TRadians<O>() const
	{
		return ToRadians<O>();
	}

	template<TIsRealType O> requires TIsGreaterEqualsThen<O, T>
	inline constexpr operator TRadians<O>() const
	{
		return ToRadians<O>();
	}

	inline constexpr bool operator ==(const TDegrees& rh) const
	{
		return Value == rh.Value;
	}

	inline constexpr bool operator !=(const TDegrees& rh) const
	{
		return Value != rh.Value;
	}

	inline constexpr bool operator <(const TDegrees& rh) const
	{
		return Value < rh.Value;
	}

	inline constexpr bool operator >(const TDegrees& rh) const
	{
		return Value > rh.Value;
	}

	inline constexpr bool operator <=(const TDegrees& rh) const
	{
		return Value <= rh.Value;
	}

	inline constexpr bool operator >=(const TDegrees& rh) const
	{
		return Value >= rh.Value;
	}
};

template<TIsRealType T>
inline constexpr TDegrees<T> operator *(const T& lh, const TDegrees<T>& rh)
{
	return TDegrees<T>(lh * rh.Value);
}

template<TIsRealType T>
inline constexpr TDegrees<T> operator /(const T& lh, const TDegrees<T>& rh)
{
	return TDegrees<T>(lh / rh.Value);
}

/// <summary>
/// 라디안 단위를 래핑합니다.
/// </summary>
template<TIsRealType T = float>
struct TRadians
{
private:
	static constexpr T PI = (T)3.141592;
	static constexpr T Inv180 = (T)180.0 / PI;
	static constexpr T AngleMax = PI * (T)2;
	static constexpr T AngleHalf = PI;

public:
	T Value;

	/// <summary>
	/// 초기화되지 않은 개체를 가져옵니다.
	/// </summary>
	inline TRadians()
	{

	}

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="value"> 초기화 값을 전달합니다. </param>
	inline constexpr TRadians(const T& value) : Value(value)
	{

	}

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="value"> 초기화 값을 전달합니다. </param>
	inline constexpr TRadians(const TRadians& value) : Value(value.Value)
	{

	}

	/// <summary>
	/// 개체의 간단한 텍스트 설명을 가져옵니다.
	/// </summary>
	/// <returns> 텍스트 개체가 반환됩니다. </returns>
	inline SString* ToString() const
	{
		return SString::Format(L"{0}rad", Value);
	}

	/// <summary>
	/// 라디안 단위로 한정된 값을 가져옵니다.
	/// </summary>
	/// <returns> 한정된 값이 반환됩니다. </returns>
	inline constexpr TRadians GetClamped() const;

	/// <summary>
	/// 라디안 단위로 한정된 값을 가져옵니다.
	/// </summary>
	/// <returns> 한정된 값이 반환됩니다. </returns>
	inline constexpr TRadians GetNormalized() const;

	/// <summary>
	/// 각도 단위로 변환합니다.
	/// </summary>
	/// <returns> 변환된 각도 값이 반환됩니다. </returns>
	template<TIsRealType O = T>
	inline constexpr TDegrees<O> ToDegrees() const;

	inline TRadians& operator =(const TRadians& value)
	{
		Value = value.Value;
		return *this;
	}

	inline TRadians& operator +=(const TRadians& value)
	{
		Value += value.Value;
		return *this;
	}

	inline TRadians& operator -=(const TRadians& value)
	{
		Value -= value.Value;
		return *this;
	}

	inline TRadians& operator *=(const T& value)
	{
		Value *= value;
		return *this;
	}

	inline TRadians& operator /=(const T& value)
	{
		Value /= value;
		return *this;
	}

	inline constexpr TRadians operator -() const
	{
		return TRadians(-Value);
	}

	inline constexpr TRadians operator +(const TRadians& value) const
	{
		return TRadians(Value + value.Value);
	}

	inline constexpr TRadians operator -(const TRadians& value) const
	{
		return TRadians(Value - value.Value);
	}

	inline constexpr TRadians operator *(const T& value) const
	{
		return TRadians(Value * value);
	}

	inline constexpr TRadians operator /(const T& value) const
	{
		return TRadians(Value / value);
	}

	template<TIsRealType O> requires TIsSmallThen<O, T>
	inline constexpr explicit operator TRadians<O>() const
	{
		return TRadians<O>(static_cast<O>(Value));
	}

	template<TIsRealType O> requires TIsGreaterEqualsThen<O, T>
	inline constexpr operator TRadians<O>() const
	{
		return TRadians<O>(static_cast<O>(Value));
	}

	template<TIsRealType O> requires TIsSmallThen<O, T>
	inline constexpr explicit operator TDegrees<O>() const
	{
		return ToDegrees<O>();
	}

	template<TIsRealType O> requires TIsGreaterEqualsThen<O, T>
	inline constexpr operator TDegrees<O>() const
	{
		return ToDegrees<O>();
	}

	inline constexpr bool operator ==(const TRadians& rh) const
	{
		return Value == rh.Value;
	}

	inline constexpr bool operator !=(const TRadians& rh) const
	{
		return Value != rh.Value;
	}

	inline constexpr bool operator <(const TRadians& rh) const
	{
		return Value < rh.Value;
	}

	inline constexpr bool operator >(const TRadians& rh) const
	{
		return Value > rh.Value;
	}

	inline constexpr bool operator <=(const TRadians& rh) const
	{
		return Value <= rh.Value;
	}

	inline constexpr bool operator >=(const TRadians& rh) const
	{
		return Value >= rh.Value;
	}
};

template<TIsRealType T>
inline constexpr TRadians<T> operator *(const T& lh, const TRadians<T>& rh)
{
	return TRadians<T>(lh * rh.Value);
}

template<TIsRealType T>
inline constexpr TRadians<T> operator /(const T& lh, const TRadians<T>& rh)
{
	return TRadians<T>(lh / rh.Value);
}

template<TIsRealType T>
inline constexpr TDegrees<T> TDegrees<T>::GetClamped() const
{
	return Math::Mod(Value, AngleMax);
}

template<TIsRealType T>
inline constexpr TDegrees<T> TDegrees<T>::GetNormalized() const
{
	TDegrees clamped = GetClamped();
	if (clamped.Value > AngleHalf)
	{
		return clamped.Value - AngleMax;
	}
	else
	{
		return clamped;
	}
}

template<TIsRealType T>
template<TIsRealType O>
inline constexpr TRadians<O> TDegrees<T>::ToRadians() const
{
	return Value * InvPI;
}

template<TIsRealType T>
inline constexpr TRadians<T> TRadians<T>::GetClamped() const
{
	return Math::Mod(Value, AngleMax);
}

template<TIsRealType T>
inline constexpr TRadians<T> TRadians<T>::GetNormalized() const
{
	TRadians clamped = GetClamped();
	if (clamped.Value > AngleHalf)
	{
		return clamped.Value - AngleMax;
	}
	else
	{
		return clamped;
	}
}

template<TIsRealType T>
template<TIsRealType O>
inline constexpr TDegrees<O> TRadians<T>::ToDegrees() const
{
	return static_cast<O>(Value) * static_cast<O>(Inv180);
}

using Radians = TRadians<float>;
using Degrees = TDegrees<float>;

inline constexpr Degrees operator"" _deg(long double value)
{
	return (float)value;
}

inline constexpr Radians operator "" _rad(long double value)
{
	return (float)value;
}
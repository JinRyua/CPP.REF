// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <chrono>
#include <compare>

struct Nanoseconds;

template<class T>
concept TIsDuration = requires(T* Derived, Nanoseconds* Super)
{
	{ Super = Derived };
};

template<class T>
concept TIsRatio = requires()
{
	{ T::den };
	{ T::num };
};

namespace Duration_Implementation
{
	template<size_t N>
	struct TimeStringLit
	{
		char C_Str[N];

		consteval TimeStringLit(const char(&text)[N]);
		template<size_t... Seq>
		consteval TimeStringLit(const char(&text)[N], std::index_sequence<Seq...>&&);
	};
}

/// <summary>
/// 나노초 단위의 값을 래핑합니다.
/// </summary>
struct Nanoseconds
{
	using This = Nanoseconds;
	using Mychrono = std::chrono::nanoseconds;

	/// <summary>
	/// 단위 값을 나타냅니다.
	/// </summary>
	Mychrono Unit;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	inline Nanoseconds();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="value"> 나노초 값을 전달합니다. </param>
	inline constexpr Nanoseconds(int64 value);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <typeparam name="T"> 초기화 값의 시간 형식을 전달합니다. </typeparam>
	/// <param name="value"> 초기화 값을 전달합니다. </param>
	template<class T>
	inline constexpr Nanoseconds(std::chrono::duration<int64, T> value);

	/// <summary>
	/// 대상 시간 값과 일치하는지 검사합니다.
	/// </summary>
	/// <param name="rh"> 대상 시간 값을 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	inline constexpr bool Equals(const Nanoseconds& rh) const;

	/// <summary>
	/// 시간의 단순 텍스트 설명을 가져옵니다.
	/// </summary>
	/// <returns> 텍스트 개체가 반환됩니다. </returns>
	inline SString* ToString() const;

	/// <summary>
	/// 나노초 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	inline constexpr int64 GetValue() const;

	/// <summary>
	/// 나노초 값을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	inline void SetValue(int64 value);

	inline constexpr bool operator ==(const Nanoseconds& rh) const;
	inline constexpr bool operator !=(const Nanoseconds& rh) const;
	inline constexpr bool operator < (const Nanoseconds& rh) const;
	inline constexpr bool operator <=(const Nanoseconds& rh) const;
	inline constexpr bool operator > (const Nanoseconds& rh) const;
	inline constexpr bool operator >=(const Nanoseconds& rh) const;
	inline constexpr std::weak_ordering operator <=>(const Nanoseconds& rh) const;

	template<TIsDuration T>
	inline constexpr operator T () const;

	inline constexpr Nanoseconds operator +(const Nanoseconds& rh) const;
	inline constexpr Nanoseconds operator -(const Nanoseconds& rh) const;
	
	inline Nanoseconds& operator +=(const Nanoseconds& rh);
	inline Nanoseconds& operator -=(const Nanoseconds& rh);
};

/// <summary>
/// 나노초를 제외한 초 단위 값을 래핑합니다.
/// </summary>
template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
struct Subseconds : public Nanoseconds
{
	using Super = Nanoseconds;
	using This = Subseconds;
	using Mychrono = std::chrono::duration<float, TRatio>;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	inline constexpr Subseconds();

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="nano"> 나노초 값을 전달합니다. </param>
	inline constexpr Subseconds(int64 nano);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="value"> 형식에 맞는 시간 값을 전달합니다. </param>
	inline constexpr Subseconds(float value);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="nano"> 나노초 값을 전달합니다. </param>
	inline constexpr Subseconds(const Nanoseconds& nano);

	/// <summary>
	/// 시간의 단순 텍스트 설명을 가져옵니다.
	/// </summary>
	/// <returns> 텍스트 개체가 반환됩니다. </returns>
	inline SString* ToString() const;

	/// <summary>
	/// 형식에 맞는 시간 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	inline constexpr float GetValue() const;

	/// <summary>
	/// 형식에 맞는 시간 값을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	inline void SetValue(float value);

	inline Subseconds& operator =(const Nanoseconds& rh);
	inline Subseconds& operator +=(const Nanoseconds& rh);
	inline Subseconds& operator -=(const Nanoseconds& rh);
};

#include "Duration.inl"

using Microseconds = Subseconds<std::micro, "μs">;
using Milliseconds = Subseconds<std::milli, "ms">;
using Seconds = Subseconds<std::ratio<1>, "s">;
using Minutes = Subseconds<std::ratio<60>, "m">;
using Hours = Subseconds<std::ratio<3600>, "h">;
using Days = Subseconds<std::ratio<86400>, "d">;
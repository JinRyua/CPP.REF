// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Duration.h"
#include "Core/String.h"

template<size_t N>
consteval Duration_Implementation::TimeStringLit<N>::TimeStringLit(const char(&text)[N]) : TimeStringLit(text, std::make_index_sequence<N>{ })
{

}

template<size_t N>
template<size_t... Seq>
consteval Duration_Implementation::TimeStringLit<N>::TimeStringLit(const char(&text)[N], std::index_sequence<Seq...>&&)
	: C_Str{ text[Seq]... }
{

}

inline Nanoseconds::Nanoseconds()
{

}

inline constexpr Nanoseconds::Nanoseconds(int64 value) : Unit(Mychrono(value))
{

}

template<class T>
inline constexpr Nanoseconds::Nanoseconds(std::chrono::duration<int64, T> value) : Unit(value)
{

}

inline constexpr bool Nanoseconds::Equals(const Nanoseconds& rh) const
{
	return *this == rh;
}

inline SString* Nanoseconds::ToString() const
{
	return SString::Format("{0}ns"_s, Unit.count());
}

inline constexpr int64 Nanoseconds::GetValue() const
{
	return Unit.count();
}

inline void Nanoseconds::SetValue(int64 value)
{
	Unit = Mychrono(value);
}

inline constexpr bool Nanoseconds::operator ==(const Nanoseconds& rh) const
{
	return Unit == rh.Unit;
}

inline constexpr bool Nanoseconds::operator !=(const Nanoseconds& rh) const
{
	return Unit != rh.Unit;
}

inline constexpr bool Nanoseconds::operator < (const Nanoseconds& rh) const
{
	return Unit < rh.Unit;
}

inline constexpr bool Nanoseconds::operator <=(const Nanoseconds& rh) const
{
	return Unit <= rh.Unit;
}

inline constexpr bool Nanoseconds::operator > (const Nanoseconds& rh) const
{
	return Unit > rh.Unit;
}

inline constexpr bool Nanoseconds::operator >=(const Nanoseconds& rh) const
{
	return Unit >= rh.Unit;
}

inline constexpr std::weak_ordering Nanoseconds::operator <=>(const Nanoseconds& rh) const
{
	return Unit.count() <=> rh.Unit.count();
}

template<TIsDuration T>
inline constexpr Nanoseconds::operator T () const
{
	return T(Unit.count());
}

inline constexpr Nanoseconds Nanoseconds::operator +(const Nanoseconds& rh) const
{
	return Unit + rh.Unit;
}

inline constexpr Nanoseconds Nanoseconds::operator -(const Nanoseconds& rh) const
{
	return Unit - rh.Unit;
}

inline Nanoseconds& Nanoseconds::operator +=(const Nanoseconds& rh)
{
	Unit += rh.Unit;
	return *this;
}

inline Nanoseconds& Nanoseconds::operator -=(const Nanoseconds& rh)
{
	Unit -= rh.Unit;
	return *this;
}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline constexpr Subseconds<TRatio, TimeStr>::Subseconds()
{

}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline constexpr Subseconds<TRatio, TimeStr>::Subseconds(int64 nano) : Super(nano)
{

}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline constexpr Subseconds<TRatio, TimeStr>::Subseconds(float value) : Super(std::chrono::duration_cast<Super::Mychrono>(Mychrono(value)).count())
{

}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline constexpr Subseconds<TRatio, TimeStr>::Subseconds(const Nanoseconds& nano) : Super(nano.Unit)
{

}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline SString* Subseconds<TRatio, TimeStr>::ToString() const
{
	return SString::Format("{0}{1}"_s, GetValue(), TimeStr.C_Str);
}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline constexpr float Subseconds<TRatio, TimeStr>::GetValue() const
{
	return std::chrono::duration_cast<Mychrono>(Unit).count();
}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline void Subseconds<TRatio, TimeStr>::SetValue(float value)
{
	Unit = std::chrono::duration_cast<Super::Mychrono>(Mychrono(value));
}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline auto Subseconds<TRatio, TimeStr>::operator =(const Nanoseconds& rh) -> Subseconds&
{
	Unit = rh.Unit;
	return *this;
}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline auto Subseconds<TRatio, TimeStr>::operator +=(const Nanoseconds& rh) -> Subseconds&
{
	Unit += rh.Unit;
	return *this;
}

template<TIsRatio TRatio, Duration_Implementation::TimeStringLit TimeStr>
inline auto Subseconds<TRatio, TimeStr>::operator -=(const Nanoseconds& rh) -> Subseconds&
{
	Unit -= rh.Unit;
	return *this;
}
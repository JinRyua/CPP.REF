// Copyright 2020-2021 Aumoa.lib. All right reserved.

export module SC.Runtime.Core:Degrees;

import std.core;
import :MathEx;
import :Radians;
import :StringUtils;

using namespace std;

/// <summary>
/// Represents the degrees value.
/// </summary>
export struct Degrees
{
	float Value = 0;

	/// <summary>
	/// Initialize new <see cref="Degrees"/> instance.
	/// </summary>
	inline constexpr Degrees()
	{
	}

	/// <summary>
	/// Initialize new <see cref="Degrees"/> instance.
	/// </summary>
	/// <param name="value"> The initial value. </param>
	inline constexpr Degrees(float value) : Value(value)
	{
	}

	/// <summary>
	/// Get simple string represents this degrees value.
	/// </summary>
	/// <param name="formatArgs"> The formatting args that use to std::format. </param>
	/// <returns> The simple string value. </returns>
	inline wstring ToString(wstring_view formatArgs = L"") const
	{
		wstring placeholder = StringUtils::GetPlaceholder(formatArgs) + L"��";
		return format(placeholder, Value);
	}

	/// <summary>
	/// Compare nearly equals to target degrees with epsilon value.
	/// </summary>
	/// <param name="rhs"> The target degrees. </param>
	/// <param name="epsilon"> The epsilon value. If different of two components is lower than this values, is nearly equals. </param>
	/// <returns> Indicate two degrees is nearly equals. </returns>
	inline constexpr bool NearlyEquals(const Degrees& rhs, float epsilon) const
	{
		return MathEx::Abs(Value - rhs.Value) <= epsilon;
	}

	/// <summary>
	/// Get clamped angle.
	/// </summary>
	/// <returns> The clamped value. </returns>
	inline constexpr Degrees GetClamped() const
	{
		return MathEx::Mod(Value, AngleMax);
	}

	/// <summary>
	/// Get normalized angle.
	/// </summary>
	/// <returns> The normalized value. </returns>
	inline constexpr Degrees GetNormal() const
	{
		Degrees clamped = GetClamped();
		if (clamped.Value > AngleHalf)
		{
			return clamped.Value - AngleMax;
		}
		else
		{
			return clamped;
		}
	}

	/// <summary>
	/// Convert degrees to radians.
	/// </summary>
	/// <returns> The degrees value. </returns>
	inline constexpr Radians ToRadians() const
	{
		return Radians(Value * PI180);
	}

	inline constexpr bool operator ==(const Degrees& rhs) const
	{
		return Value == rhs.Value;
	}

	inline constexpr bool operator !=(const Degrees& rhs) const
	{
		return Value != rhs.Value;
	}

	inline constexpr auto operator <(const Degrees& rhs) const
	{
		return Value < rhs.Value;
	}

	inline constexpr auto operator <=(const Degrees& rhs) const
	{
		return Value <= rhs.Value;
	}

	inline constexpr auto operator >(const Degrees& rhs) const
	{
		return Value > rhs.Value;
	}

	inline constexpr auto operator >=(const Degrees& rhs) const
	{
		return Value >= rhs.Value;
	}

	inline Degrees& operator =(const Degrees& rhs)
	{
		Value = rhs.Value;
		return *this;
	}

	inline Degrees& operator +=(const Degrees& rhs)
	{
		Value += rhs.Value;
		return *this;
	}

	inline Degrees& operator -=(const Degrees& rhs)
	{
		Value -= rhs.Value;
		return *this;
	}

	inline Degrees& operator *=(const Degrees& rhs)
	{
		Value *= rhs.Value;
		return *this;
	}

	inline Degrees& operator /=(const Degrees& rhs)
	{
		Value /= rhs.Value;
		return *this;
	}

	inline constexpr Degrees operator -() const
	{
		return Degrees(-Value);
	}

	inline constexpr Degrees operator +(const Degrees& rhs) const
	{
		return Degrees(Value + rhs.Value);
	}

	inline constexpr Degrees operator -(const Degrees& rhs) const
	{
		return Degrees(Value - rhs.Value);
	}

	inline constexpr Degrees operator *(const Degrees& rhs) const
	{
		return Degrees(Value * rhs.Value);
	}

	inline constexpr Degrees operator /(const Degrees& rhs) const
	{
		return Degrees(Value / rhs.Value);
	}

private:
	static constexpr float AngleHalf = 180.0f;
	static constexpr float AngleMax = AngleHalf * 2.0f;
	static constexpr float PI180 = numbers::pi_v<float> / 180.0f;
};

export inline constexpr Degrees Radians::ToDegrees() const
{
	return Value * _180PI;
}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

export module SC.Runtime.Core:Vector4;

import :Vector;

export struct Vector4 : public Vector<4>
{
	/// <summary>
	/// Initialize new <see cref="Vector4"/> instance.
	/// </summary>
	inline constexpr Vector4()
	{
	}

	/// <summary>
	/// Initialize new <see cref="Vector4"/> instance.
	/// </summary>
	/// <param name="initializer"> The initializer to initialize vector values. </param>
	inline constexpr Vector4(std::initializer_list<float> initializer)
	{
		for (size_t i = 0; i < MathEx::Min(initializer.size(), Num()); ++i)
		{
			Values[i] = initializer.begin()[i];
		}
	}

	/// <summary>
	/// Initialize new <see cref="Vector4"/> instance.
	/// </summary>
	/// <param name="copy"> The copy vector to initialize vector values. </param>
	inline constexpr Vector4(const Vector<4>& copy)
	{
		for (size_t i = 0; i < Num(); ++i)
		{
			Values[i] = copy[i];
		}
	}

	/// <summary>
	/// Initialize new <see cref="Vector4"/> instance.
	/// </summary>
	/// <param name="copy"> The copy vector to initialize vector values. </param>
	/// <param name="fill"> The fill value for placed without initialization. </param>
	template<size_t ON>
	inline constexpr Vector4(const Vector<ON>& copy, float fill = 0.0f)
	{
		for (size_t i = 0; i < Num(); ++i)
		{
			if (i < ON) {
				Values[i] = copy[i];
			}
			else {
				Values[i] = fill;
			}
		}
	}

	/// <summary>
	/// Get X component.
	/// </summary>
	/// <returns> Reference of X component. </returns>
	inline constexpr const float& X() const
	{
		return Values[0];
	}

	/// <summary>
	/// Get Y component.
	/// </summary>
	/// <returns> Reference of Y component. </returns>
	inline constexpr const float& Y() const
	{
		return Values[1];
	}

	/// <summary>
	/// Get Z component.
	/// </summary>
	/// <returns> Reference of Z component. </returns>
	inline constexpr const float& Z() const
	{
		return Values[2];
	}

	/// <summary>
	/// Get W component.
	/// </summary>
	/// <returns> Reference of W component. </returns>
	inline constexpr const float& W() const
	{
		return Values[3];
	}

	/// <summary>
	/// Get X component.
	/// </summary>
	/// <returns> Reference of X component. </returns>
	inline float& X()
	{
		return Values[0];
	}

	/// <summary>
	/// Get Y component.
	/// </summary>
	/// <returns> Reference of Y component. </returns>
	inline float& Y()
	{
		return Values[1];
	}

	/// <summary>
	/// Get W component.
	/// </summary>
	/// <returns> Reference of W component. </returns>
	inline float& W()
	{
		return Values[3];
	}
};
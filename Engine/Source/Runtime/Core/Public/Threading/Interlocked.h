// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

/// <summary>
/// 스레드 안전한 원자 연산을 수행하는 함수를 제공합니다.
/// </summary>
class CORE_API Interlocked : virtual public SObject
{
private:
	Interlocked() = delete;

public:
	/// <summary>
	/// 64비트 정수형 값을 1 증가시킵니다.
	/// </summary>
	/// <param name="value"> 값의 참조를 전달합니다. </param>
	/// <returns> 증가된 값이 반환됩니다. </returns>
	static int64 Increment64(int64& value);

	/// <summary>
	/// 64비트 정수형 값을 1 감소시킵니다.
	/// </summary>
	/// <param name="value"> 값의 참조를 전달합니다. </param>
	/// <returns> 감소된 값이 반환됩니다. </returns>
	static int64 Decrement64(int64& value);
};
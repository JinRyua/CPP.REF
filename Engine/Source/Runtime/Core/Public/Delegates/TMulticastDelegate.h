// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TFunction.h"

/// <summary>
/// 대리자 목록을 표현합니다.
/// </summary>
/// <typeparam name="T"> 다중 대리자 함수 형식을 전달합니다. </typeparam>
template<class T>
class TMulticastDelegate
{
	static_assert(false);
};

/// <summary>
/// 대리자 목록을 표현합니다. 
/// </summary>
/// <typeparam name="...TArgs"> 다중 대리자 함수의 매개변수입니다. </typeparam>
template<class... TArgs>
class TMulticastDelegate<void(TArgs...)>
{
public:
	/// <summary>
	/// 개체의 새 인스턴스를 초기화합니다.
	/// </summary>
	TMulticastDelegate()
	{

	}
};
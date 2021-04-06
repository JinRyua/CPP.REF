// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <vector>
#include "TFunction.h"

/// <summary>
/// 대리자 목록을 표현합니다.
/// </summary>
/// <typeparam name="T"> 다중 대리자 함수 형식을 전달합니다. </typeparam>
template<class T>
class TMulticastDelegate
{

};

/// <summary>
/// 대리자 목록을 표현합니다. 
/// </summary>
/// <typeparam name="...TArgs"> 다중 대리자 함수의 매개변수입니다. </typeparam>
template<class... TArgs>
class TMulticastDelegate<void(TArgs...)>
{
	std::vector<TFunction<void(TArgs...)>> functions;

public:
	/// <summary>
	/// 개체의 새 인스턴스를 초기화합니다.
	/// </summary>
	TMulticastDelegate()
	{

	}

	/// <summary>
	/// 등록된 모든 함수를 호출합니다.
	/// </summary>
	/// <param name="...inArgs"> 함수 호출 매개변수를 전달합니다. </param>
	void Broadcast(TArgs&&... inArgs)
	{
		for (auto& item : functions)
		{
			item.Invoke(std::forward<TArgs>(inArgs)...);
		}
	}
};
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

/// <summary>
/// 종료자 패턴을 구현한 형식에 대한 공통 인터페이스를 제공합니다.
/// </summary>
SINTERFACE(IDisposable) interface IDisposable : virtual public SObject
{
	virtual void Dispose() = 0;
};
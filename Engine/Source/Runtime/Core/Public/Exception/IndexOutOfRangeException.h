// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Exception.h"

/// <summary>
/// 인덱스가 범위를 벗어났을 때 발생하는 예외입니다.
/// </summary>
SCLASS(SIndexOutOfRangeException) class CORE_API SIndexOutOfRangeException : public SException
{
	SCLASS_BODY(SIndexOutOfRangeException)

public:
	/// <summary>
	/// 기본 메시지로 새 인스턴스를 초기화합니다.
	/// </summary>
	SIndexOutOfRangeException();

	/// <summary>
	/// 메시지를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	SIndexOutOfRangeException(SString* message);

	/// <summary>
	/// 메시지와 내부 예외를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	/// <param name="innerException"> 내부 예외 개체를 전달합니다. </param>
	SIndexOutOfRangeException(SString* message, SException* innerException);
	~SIndexOutOfRangeException() override;
};
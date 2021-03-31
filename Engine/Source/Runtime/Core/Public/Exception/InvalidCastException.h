// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Exception.h"

SCLASS(SInvalidCastException) class CORE_API SInvalidCastException : public SException
{
	SCLASS_BODY(SInvalidCastException)

public:
	/// <summary>
	/// 기본 메시지로 새 인스턴스를 초기화합니다.
	/// </summary>
	SInvalidCastException();

	/// <summary>
	/// 메시지를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	SInvalidCastException(SString* message);

	/// <summary>
	/// 메시지와 내부 예외를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	/// <param name="innerException"> 내부 예외 개체를 전달합니다. </param>
	SInvalidCastException(SString* message, SException* innerException);
	~SInvalidCastException() override;
};
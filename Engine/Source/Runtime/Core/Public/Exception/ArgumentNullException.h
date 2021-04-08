// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "ArgumentException.h"

/// <summary>
/// 널 매개변수를 허용하지 않는 곳에 널 매개변수를 전달했을 때 발생하는 예외입니다. 
/// </summary>
class CORE_API SArgumentNullException : public SArgumentException
{
	SCLASS_BODY(SArgumentNullException)

public:
	/// <summary>
	/// 기본 메시지로 새 인스턴스를 초기화합니다.
	/// </summary>
	SArgumentNullException();

	/// <summary>
	/// 메시지를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	SArgumentNullException(SString* message);

	/// <summary>
	/// 메시지와 내부 예외를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	/// <param name="innerException"> 내부 예외 개체를 전달합니다. </param>
	SArgumentNullException(SString* message, SException* innerException);
	~SArgumentNullException() override;
};
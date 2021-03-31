// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Exception.h"

/// <summary>
/// 지원하지 않는 기능을 사용하려 했을 때 발생하는 예외입니다.
/// </summary>
SCLASS(SNotSupportedException) class CORE_API SNotSupportedException : public SException
{
	SCLASS_BODY(SNotSupportedException)

public:
	/// <summary>
	/// 기본 메시지로 새 인스턴스를 초기화합니다.
	/// </summary>
	SNotSupportedException();

	/// <summary>
	/// 메시지를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	SNotSupportedException(SString* message);

	/// <summary>
	/// 메시지와 내부 예외를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	/// <param name="innerException"> 내부 예외 개체를 전달합니다. </param>
	SNotSupportedException(SString* message, SException* innerException);
	~SNotSupportedException() override;
};
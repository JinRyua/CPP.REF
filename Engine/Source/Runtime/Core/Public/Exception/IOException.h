// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Exception.h"

/// <summary>
/// IO 기능 수행 중 발생한 예외 정보를 제공합니다.
/// </summary>
SCLASS(SIOException) class CORE_API SIOException : public SException
{
	SCLASS_BODY(SIOException)

public:
	/// <summary>
	/// 기본 메시지로 새 인스턴스를 초기화합니다.
	/// </summary>
	SIOException();

	/// <summary>
	/// 메시지를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	SIOException(SString* message);

	/// <summary>
	/// 메시지와 내부 예외를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	/// <param name="innerException"> 내부 예외 개체를 전달합니다. </param>
	SIOException(SString* message, SException* innerException);
	~SIOException() override;
};
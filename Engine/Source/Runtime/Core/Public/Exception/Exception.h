// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

/// <summary>
/// 공통 예외 함수를 제공합니다.
/// </summary>
SCLASS(SException) class CORE_API SException : virtual public SObject
{
	SCLASS_BODY(SException)

private:
	SPROPERTY(SException*, innerException);
	SPROPERTY(SString*, message);

public:
	/// <summary>
	/// 기본 메시지로 새 인스턴스를 초기화합니다.
	/// </summary>
	SException();
	
	/// <summary>
	/// 메시지를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	SException(SString* message);

	/// <summary>
	/// 메시지와 내부 예외를 지정하여 새 인스턴스를 초기화합니다.
	/// </summary>
	/// <param name="message"> 메시지를 전달합니다. </param>
	/// <param name="innerException"> 내부 예외 개체를 전달합니다. </param>
	SException(SString* message, SException* innerException);
	virtual ~SException();

	/// <summary>
	/// 예외 메시지를 가져옵니다.
	/// </summary>
	/// <returns> 개체가 반환됩니다. </returns>
	SString* GetMessage() const;

	/// <summary>
	/// 내부 예외 개체를 가져옵니다.
	/// </summary>
	/// <returns> 개체가 반환됩니다. </returns>
	SException* GetInnerException() const;
};
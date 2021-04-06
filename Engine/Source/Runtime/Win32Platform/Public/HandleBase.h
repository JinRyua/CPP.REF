// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "CoreMinimal.h"

/// <summary>
/// Windows API에서 제공하는 핸들 서비스에 대한 공통 함수를 제공합니다.
/// </summary>
SCLASS(SHandleBase) class WIN32PLATFORM_API SHandleBase : virtual public SObject, virtual public IDisposable
{
	SCLASS_BODY(SHandleBase)

private:
	void* handle;
	bool bDisposable : 1;
	bool bDisposed : 1;

protected:
	/// <summary>
	/// 빈 개체를 초기화합니다.
	/// </summary>
	SHandleBase();

	/// <summary>
	/// 네이티브 핸들 개체를 설정합니다.
	/// </summary>
	/// <param name="handle"> 핸들 개체를 전달합니다. </param>
	/// <param name="bDisposable"> 개체가 종료 가능합니다. </param>
	void SetHandle(void* handle, bool bDisposable);

public:
	~SHandleBase() override;

	/// <summary>
	/// 저장된 핸들 개체를 가져옵니다.
	/// </summary>
	/// <returns> 네이티브 핸들 개체가 반환됩니다. </returns>
	void* GetHandle() const;

	/// <summary>
	/// 저장된 핸들 개체를 가져옵니다.
	/// </summary>
	/// <returns> 형식 변환 된 핸들 개체가 반환됩니다. </returns>
	template<class T>
	T GetHandle() const
	{
		return (T)GetHandle();
	}

	/// <summary>
	/// 개체의 사용을 종료하고 리소스를 반환합니다.
	/// </summary>
	virtual void Dispose();
};
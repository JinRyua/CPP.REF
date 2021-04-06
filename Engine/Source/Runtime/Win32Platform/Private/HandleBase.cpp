// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Win32Platform.h"
#include "HandleBase.h"

SHandleBase::SHandleBase() : Super()
	, handle(nullptr)
	, bDisposable(false)
	, bDisposed(false)
{

}

void SHandleBase::SetHandle(void* handle, bool bDisposable)
{
	if (bDisposed)
	{
		throw new SInvalidOperationException("개체가 이미 종료되었습니다."_s);
	}

	this->handle = handle;
	this->bDisposable = bDisposable;
}

SHandleBase::~SHandleBase()
{
	if (bDisposable && !bDisposed)
	{
		throw new SInvalidOperationException("개체가 종료 가능한데, 종료되지 않은 채 소멸하려 합니다."_s);
	}
}

void* SHandleBase::GetHandle() const
{
	return handle;
}

void SHandleBase::Dispose()
{
	if (!bDisposed)
	{
		if (bDisposable)
		{
			CloseHandle(handle);
		}
		handle = nullptr;
		bDisposed = true;
	}
}
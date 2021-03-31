// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Reflection/PropertyRegister.h"

using namespace Reflection;

void PropertyRegisterBase::SafeAddRef(SObject* object)
{
	if (object != nullptr)
	{
		object->AddRefInterlocked();
	}
}

void PropertyRegisterBase::SafeRelease(SObject* object)
{
	if (object != nullptr)
	{
		object->ReleaseInterlocked();
	}
}
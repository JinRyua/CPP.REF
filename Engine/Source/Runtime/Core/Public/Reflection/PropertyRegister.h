// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/CoreConcepts.h"
#include "Core/Object.h"

#pragma warning(disable: 4251)

namespace Reflection
{
	struct CORE_API PropertyRegisterBase
	{
		static void SafeAddRef(SObject* object);
		static void SafeRelease(SObject* object);
	};

	template<class T>
	struct PropertyRegisterImpl : public PropertyRegisterBase
	{
		PropertyRegisterImpl(T* inReference)
		{
		}

		~PropertyRegisterImpl()
		{
		}

		void SafeAddRef()
		{
		}

		void SafeRelease()
		{
		}
	};

	template<class TSubclass>
	struct PropertyRegisterImpl<TSubclass*> : public PropertyRegisterBase
	{
		TSubclass** const Reference;

		PropertyRegisterImpl(TSubclass** inReference) : Reference(inReference)
		{

		}

		~PropertyRegisterImpl()
		{
			SafeRelease();
		}

		void SafeAddRef()
		{
			PropertyRegisterBase::SafeAddRef(*Reference);
		}

		void SafeRelease()
		{
			PropertyRegisterBase::SafeRelease(*Reference);
			*Reference = nullptr;
		}
	};
}

#define SPROPERTY(MemberType, MemberName, ...) \
	MemberType DECLARE_ ## MemberName = {};\
	\
	__declspec(property(get = MemberName ## _get, put = MemberName ## _set)) MemberType MemberName;\
	MemberType MemberName ## _get() const\
	{\
		return DECLARE_ ## MemberName;\
	}\
	\
	void MemberName ## _set(MemberType value)\
	{\
		if constexpr (TIsObject<typename TRemovePointer<MemberType>::Type>)\
		{\
			REGISTER_ ## MemberName.SafeRelease();\
			DECLARE_ ## MemberName = value;\
			REGISTER_ ## MemberName.SafeAddRef();\
		}\
		else\
		{\
			DECLARE_ ## MemberName = value;\
		}\
	}\
	\
	template<>\
	constexpr static bool SPROPERTY_Counter<__COUNTER__ - 1>()\
	{\
		return true;\
	}\
	\
	Reflection::PropertyRegisterImpl<MemberType> REGISTER_ ## MemberName = &DECLARE_ ## MemberName;
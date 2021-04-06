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
		size_t MemberOffset;
		const char* MemberName;

		PropertyRegisterImpl(size_t memberOffset, const char* memberName)
			: MemberOffset(memberOffset)
			, MemberName(memberName)
		{
		}

		~PropertyRegisterImpl()
		{
		}
	};
}

//#define SPROPERTY_MemberOffset(Type, Member) reinterpret_cast<size_t>(&(reinterpret_cast<Type*>(0))->Member)
#define SPROPERTY_MemberOffset(Type, Member) __builtin_offsetof(Type, Member)

#define SPROPERTY(MemberType, MemberName, ...) \
	MemberType MemberName = {};\
	\
	template<>\
	constexpr static Reflection::SPropertyMemberDeclare SPROPERTY_Counter<__COUNTER__ - 1>()\
	{\
		return { SPROPERTY_MemberOffset(This, MemberName), #MemberName };\
	}
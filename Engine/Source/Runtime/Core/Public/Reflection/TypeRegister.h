// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "UniqueType.h"
#include <utility>
#include "Reflection/TypeCollection.h"

#pragma warning(disable: 4275)

namespace Reflection
{
	template<size_t N>
	struct StringLiteral
	{
		constexpr StringLiteral(const char(&inString)[N]) : StringLiteral(inString, std::make_index_sequence<N>{})
		{

		}

		template<size_t... I>
		constexpr StringLiteral(const char(&inString)[N], std::index_sequence<I...>&&) : MyString{ inString[I]... }
		{

		}

		char MyString[N];
	};

	template<class TClass>
	struct TypeMetaImpl : public TypeCollection::TypeMetaBase
	{
		using This = TClass;

		size_t CounterBase;

		constexpr TypeMetaImpl(const char* pClassName, size_t inCounterBase)
			: TypeMetaBase(pClassName, TUniqueType<This>::HashCode)
			, CounterBase(inCounterBase)
		{

		}
	};

	template<class TClass>
	struct TypeRegisterImpl : public TypeCollection::TypeRegisterBase
	{
		TypeRegisterImpl(const TypeMetaImpl<TClass>& metaImpl)
		{
			TypeCollection::AddType(this, metaImpl);
		}
	};
}

#define SCLASS(ClassType) \
constexpr Reflection::TypeMetaImpl<class ClassType> REFLECTION_DECLARE_ ## ClassType ## _META(#ClassType, __COUNTER__);\
__declspec(selectany) Reflection::TypeRegisterImpl<class ClassType> REFLECTION_DECLARE_ ## ClassType ## _REGISTER(REFLECTION_DECLARE_ ## ClassType ## _META);

#define SINTERFACE(InterfaceType) \
constexpr Reflection::TypeMetaImpl<interface InterfaceType> REFLECTION_DECLARE_ ## InterfaceType ## _META(#InterfaceType, __COUNTER__);\
__declspec(selectany) Reflection::TypeRegisterImpl<interface InterfaceType> REFLECTION_DECLARE_ ## InterfaceType ## _REGISTER(REFLECTION_DECLARE_ ## InterfaceType ## _META);

#define SCLASS_BODY(ClassType) \
	friend struct Reflection::TypeMetaImpl<ClassType>;\
	friend class TypeCollection;\
	\
public:\
	using Super = This;\
	using This = ClassType;\
	\
private:\
	template<size_t N>\
	constexpr static bool SPROPERTY_Counter()\
	{\
		return false;\
	}\
	\
	template<size_t Counter>\
	constexpr static auto SPROPERTY_GetPropertyChain()\
	{\
		constexpr bool b = SPROPERTY_Counter<Counter>();\
		if constexpr (b)\
		{\
			return SPROPERTY_GetPropertyChain<Counter + 1>();\
		}\
		else\
		{\
			return Counter - REFLECTION_DECLARE_ ## ClassType ## _META.CounterBase;\
		}\
	}\
	\
private:
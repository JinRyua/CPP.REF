// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "UniqueType.h"
#include <utility>
#include "Reflection/TypeCollection.h"

#pragma warning(disable: 4275)

#define SCLASS_BODY(ClassType) \
private:\
	using SPROPERTY_CounterFunctionCall = Reflection::SPropertyMemberDeclare(*)();\
	\
	class TypeRegisterImpl : public TypeCollection::TypeRegisterBase\
	{\
	public:\
		constexpr static size_t CounterBase = __COUNTER__;\
		constexpr static const char* Name = #ClassType;\
		\
		TypeRegisterImpl();\
		\
		consteval static size_t GetPropertyCount();\
		template<size_t Count>\
		consteval static std::array<SPROPERTY_CounterFunctionCall, Count> GetPropertyChain();\
		\
	private:\
		template<size_t Index>\
		consteval static auto GetPropertyCountImpl();\
		template<size_t... Indexes>\
		consteval static std::array<SPROPERTY_CounterFunctionCall, sizeof...(Indexes)> GetPropertyChainImpl(std::index_sequence<Indexes...>&&);\
	};\
	\
protected:\
	static TypeRegisterImpl TypeRegister;\
	\
private:\
	template<size_t N>\
	static consteval SPROPERTY_CounterFunctionCall SPROPERTY_GetPropertyCounter()\
	{\
		return nullptr;\
	}\
	\
	template<size_t N>\
	static Reflection::SPropertyMemberDeclare SPROPERTY_GetPropertyChain()\
	{\
		return {};\
	}\
	\
public:\
	using Super = This;\
	using This = ClassType;

#define SCLASS_BODY_IMPL(ClassType) \
template<size_t Index>\
consteval auto ClassType::TypeRegisterImpl::GetPropertyCountImpl()\
{\
	constexpr bool b = ClassType::template SPROPERTY_GetPropertyCounter<Index>() != nullptr;\
	if constexpr (b)\
	{\
		return GetPropertyCountImpl<Index + 1>();\
	}\
	else\
	{\
		return Index;\
	}\
}\
\
consteval size_t ClassType::TypeRegisterImpl::GetPropertyCount()\
{\
	return GetPropertyCountImpl<0>();\
}\
\
template<size_t Count>\
consteval auto ClassType::TypeRegisterImpl::GetPropertyChain() -> std::array<SPROPERTY_CounterFunctionCall, Count>\
{\
	return GetPropertyChainImpl(std::make_index_sequence<Count>{});\
}\
\
template<size_t... Indexes>\
consteval auto ClassType::TypeRegisterImpl::GetPropertyChainImpl(std::index_sequence<Indexes...>&&) -> std::array<SPROPERTY_CounterFunctionCall, sizeof...(Indexes)>\
{\
	return { ClassType::template SPROPERTY_GetPropertyCounter<Indexes>()... };\
}\
\
ClassType::TypeRegisterImpl::TypeRegisterImpl()\
{\
	RttiTypeId = typeid(This).hash_code();\
	ClassName = Name;\
	TypeToObject = Reflection::TypeToObject<This>();\
	Activator = []() { return new This(); };\
	SuperClass = &Super::TypeRegister;\
	\
	constexpr auto PropertyChain = GetPropertyChain<GetPropertyCount()>();\
	MemberDeclares.reserve(PropertyChain.size());\
	\
	for (size_t i = 0; i < PropertyChain.size(); ++i)\
	{\
		MemberDeclares.emplace_back(PropertyChain[i]());\
	}\
	\
	Register();\
}\
\
ClassType::TypeRegisterImpl ClassType::TypeRegister;

#define SPROPERTY_IMPL(VarType, VarName, Counter) \
	VarType VarName;\
	\
	template<>\
	static Reflection::SPropertyMemberDeclare SPROPERTY_GetPropertyChain<Counter - TypeRegisterImpl::CounterBase - 1>()\
	{\
		if constexpr (TIsObject<typename TRemovePointer<VarType>::Type>)\
		{\
			return { .Offset = __builtin_offsetof(This, VarName), .Name = #VarName, .TypeToObject = Reflection::TypeToObject<This>() };\
		}\
		else\
		{\
			return { .Offset = __builtin_offsetof(This, VarName), .Name = #VarName };\
		}\
	}\
	\
	template<>\
	static consteval SPROPERTY_CounterFunctionCall SPROPERTY_GetPropertyCounter<Counter - TypeRegisterImpl::CounterBase - 1>()\
	{\
		return &SPROPERTY_GetPropertyChain<Counter - TypeRegisterImpl::CounterBase - 1>;\
	}

#define SPROPERTY(Type, Name) SPROPERTY_IMPL(Type, Name, __COUNTER__)
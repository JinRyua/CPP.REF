// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <map>
#include <string>
#include <typeinfo>
#include <functional>
#include <array>
#include <utility>
#include "Core/CoreConcepts.h"
#include "Reflection/UniqueType.h"

#pragma warning(disable: 4251)

class SObject;
class SType;
class SString;

namespace Reflection
{
	struct SPropertyMemberDeclare
	{
		size_t Offset;
		const char* Name;

		constexpr SPropertyMemberDeclare()
			: Offset(0)
			, Name(nullptr)
		{
		}

		constexpr SPropertyMemberDeclare(size_t offset, const char* name)
			: Offset(offset)
			, Name(name)
		{
		}
	};
}

/// <summary>
/// 형식 개체에 대한 컬렉션입니다.
/// </summary>
class CORE_API TypeCollection
{
	TypeCollection() = delete;

public:
	struct TypeMetaBase
	{
		const char* pClassName;
		size_t HashCode;

		constexpr TypeMetaBase(const char* pClassName, size_t hashCode)
			: pClassName(pClassName)
			, HashCode(hashCode)
		{

		}
	};

	struct CORE_API TypeRegisterBase
	{
		static std::map<size_t, SType*>* typeCollection;
		static std::map<size_t, size_t>* rttiToUniqueType;
		static std::map<std::string, size_t>* nameToUniqueType;

		TypeRegisterBase();
		~TypeRegisterBase();
	};

public:
	/// <summary>
	/// 형식 정보를 추가합니다. 직접 사용하지 마세요.
	/// </summary>
	/// <typeparam name="TClassMetaImpl"> 클래스 메타데이터 형식을 전달합니다. </typeparam>
	/// <param name="classMeta"> 클래스 메타데이터를 전달합니다. </param>
	template<size_t CounterBase, class TClassRegisterImpl, class TClassMetaImpl>
	static void AddType(TClassRegisterImpl* classReg, const TClassMetaImpl& classMeta)
	{
		using SClass = typename TClassMetaImpl::This;
		auto properties = GetTypeProperties<SClass, CounterBase>(std::make_index_sequence<SClass::template SPROPERTY_GetPropertyChainCount<CounterBase>()>{});

		AddType_Impl(classReg, classMeta);
	}

	/// <summary>
	/// 고유 형식 정보를 가져옵니다.
	/// </summary>
	/// <param name="uniqueType"> 고유 형식 ID를 전달합니다. </param>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	static SType* GetType(size_t uniqueType);

	/// <summary>
	/// 고유 형식 정보를 가져옵니다.
	/// </summary>
	/// <typeparam name="TClass"> 고유 형식을 전달합니다. </typeparam>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	template<class TClass>
	static SType* GetType()
	{
		return GetType(Reflection::TUniqueType<TClass>::HashCode);
	}

	/// <summary>
	/// RTTI 형식 정보를 가져옵니다.
	/// </summary>
	/// <param name="rtti"> RTTI 형식을 전달합니다. </param>
	/// <returns></returns>
	static SType* GetTypeByRTTI(const std::type_info& rtti);

	/// <summary>
	/// RTTI 형식 정보를 가져옵니다.
	/// </summary>
	/// <typeparam name="TClass"> RTTI 형식을 전달합니다. </typeparam>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	template<class TClass>
	static SType* GetTypeByRTTI()
	{
		return GetTypeByRTTI(typeid(TClass));
	}

	/// <summary>
	/// 이름에 해당하는 형식 정보를 가져옵니다.
	/// </summary>
	/// <param name="typeName"> 형식 이름을 전달합니다. </param>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	static SType* GetTypeByName(const char* typeName);

	/// <summary>
	/// 이름에 해당하는 형식 정보를 가져옵니다.
	/// </summary>
	/// <param name="typeName"> 형식 이름을 전달합니다. </param>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	static SType* GetTypeByName(SString* typeName);

private:
	static void AddType(const char* className, size_t hashCode, const type_info& rttiType, std::function<SObject*()> activator);
	
	template<class TClassRegisterImpl, class TClassMetaImpl> requires THasConstructor<typename TClassMetaImpl::This>
	static void AddType_Impl(TClassRegisterImpl* classReg, const TClassMetaImpl& classMeta)
	{
		using TClass = typename TClassMetaImpl::This;
		AddType(classMeta.pClassName, classMeta.HashCode, typeid(TClassMetaImpl::This), []() -> SObject*
		{
			return new TClass();
		});
	}
	
	template<class TClassRegisterImpl, class TClassMetaImpl>
	static void AddType_Impl(TClassRegisterImpl* classReg, const TClassMetaImpl& classMeta)
	{
		using TClass = typename TClassMetaImpl::This;
		AddType(classMeta.pClassName, classMeta.HashCode, typeid(TClassMetaImpl::This), nullptr);
	}

	template<class SClass, size_t CounterBase, size_t... Indexes>
	static constexpr std::array<Reflection::SPropertyMemberDeclare, sizeof...(Indexes)> GetTypeProperties(std::index_sequence<Indexes...>&&)
	{
		return { SClass::template SPROPERTY_Counter<CounterBase + Indexes>()... };
	}
};

#define typeof(ClassType) TypeCollection::GetType<ClassType>()
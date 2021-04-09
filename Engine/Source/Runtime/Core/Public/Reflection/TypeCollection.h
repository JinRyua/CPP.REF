// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <map>
#include <string>
#include <typeinfo>
#include <functional>
#include <array>
#include <utility>
#include <optional>
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
		std::function<SObject*(void*)> TypeToObject;
		std::function<void*(SObject*)> ObjectToType;
		size_t FieldType;
	};

	template<class T>
	std::function<SObject*(void*)> TypeToObject()
	{
		static auto Caster = [](void* ptr)
		{
			T* typed = reinterpret_cast<T*>(ptr);
			return typed;
		};

		return Caster;
	}

	template<class T>
	std::function<void*(SObject*)> ObjectToType()
	{
		static auto Caster = [](SObject* ptr)
		{
			T* typed = dynamic_cast<T*>(ptr);
			return reinterpret_cast<void*>(typed);
		};

		return Caster;
	}

	template<class T>
	size_t Typeid()
	{
		return typeid(T).hash_code();
	}
}

/// <summary>
/// 형식 개체에 대한 컬렉션입니다.
/// </summary>
class CORE_API TypeCollection
{
	TypeCollection() = delete;

public:
	struct CORE_API TypeRegisterBase
	{
		friend class TypeCollection;

	private:
		static std::map<size_t, SType*>* typeCollection;
		static std::map<std::string, size_t>* nameToType;

	public:
		size_t RttiTypeId;
		const char* ClassName;
		std::function<SObject*(void*)> TypeToObject;
		std::function<void*(SObject*)> ObjectToType;
		std::vector<Reflection::SPropertyMemberDeclare> MemberDeclares;
		std::function<SObject* ()> Activator;
		TypeRegisterBase* SuperClass;

	public:
		TypeRegisterBase();
		~TypeRegisterBase();

	protected:
		void Register();
	};

public:
	/// <summary>
	/// 고유 형식 정보를 가져옵니다.
	/// </summary>
	/// <param name="rtti"> RTTI 형식을 전달합니다. </param>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	static SType* GetType(const std::type_info& rtti)
	{
		return GetType(rtti.hash_code());
	}

	/// <summary>
	/// 고유 형식 정보를 가져옵니다.
	/// </summary>
	/// <param name="rtti"> RTTI 형식을 전달합니다. </param>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	static SType* GetType(size_t rtti);

	/// <summary>
	/// 고유 형식 정보를 가져옵니다.
	/// </summary>
	/// <typeparam name="TClass"> 고유 형식을 전달합니다. </typeparam>
	/// <returns> 형식 정보 개체가 반환됩니다. </returns>
	template<class TClass>
	static SType* GetType()
	{
		return GetType(typeid(TClass));
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
};

#define typeof(ClassType) TypeCollection::GetType<ClassType>()
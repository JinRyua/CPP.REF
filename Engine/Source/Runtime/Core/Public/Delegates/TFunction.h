// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"
#include "Core/TRefPtr.h"
#include <utility>

/// <summary>
/// 단일 함수 대리자를 표현합니다.
/// </summary>
/// <typeparam name="T"> 함수 형식을 전달합니다. </typeparam>
template<class T>
class TFunction
{
};

/// <summary>
/// 단일 함수 대리자를 표현합니다.
/// </summary>
/// <typeparam name="TRet"> 함수의 반환 형식입니다. </typeparam>
/// <typeparam name="...TArgs"> 함수의 매개변수입니다. </typeparam>
template<class TRet, class... TArgs>
class TFunction<TRet(TArgs...)>
{
private:
	struct TCallableBase
	{
		virtual ~TCallableBase()
		{

		}

		virtual TRet Invoke(TArgs&&... InArgs)
		{

		}
	};

	template<class T>
	struct TCallableLambda
	{
		TCallableLambda(T&& InLambdaFunction) : Scope(std::move(InLambdaFunction))
		{

		}

		TRet Invoke(TArgs&&... InArgs) override
		{
			return Scope(std::forward<TArgs>(InArgs)...);
		}

		T Scope;
	};

	template<class TCaller>
	struct TCallableRaw
	{
		using MyFunction = TRet(TCaller::*)(TArgs...);

		TCallableRaw(TCaller* InRawPointer, TRet(TCaller::*InMemberFunc)(TArgs...))
			: RawPointer(InRawPointer)
			, MemberFunc(InMemberFunc)
		{

		}

		TRet Invoke(TArgs&&... InArgs) override
		{
			return (RawPointer->*MemberFunc)(std::forward<TArgs>(InArgs)...);
		}

		TCaller* RawPointer;
		MyFunction MemberFunc;
	};

	template<TIsObject TCaller>
	struct TCallableRef
	{
		using MyFunction = TRet(TCaller::*)(TArgs...);

		TCallableRef(const TRefPtr<TCaller>& InRefPointer, TRet(TCaller::*InMemberFunc)(TArgs...))
			: RefPointer(InRefPointer)
			, MemberFunc(InMemberFunc)
		{

		}

		TRet Invoke(TArgs&&... InArgs) override
		{
			return (RefPointer->*MemberFunc)(std::forward<TArgs>(InArgs)...);
		}

		TRefPtr<TCaller> RefPointer;
		MyFunction MemberFunc;
	};

public:
	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	TFunction()
		: Invoker(nullptr)
	{

	}

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="Mov"> 이동될 이전 개체 값을 전달합니다. </param>
	TFunction(TFunction&& Mov) noexcept
		: Invoker(Mov.Invoker)
	{
		Mov.Invoker = nullptr;
	}

	~TFunction()
	{
		if (Invoker != nullptr)
		{
			delete Invoker;
			Invoker = nullptr;
		}
	}

	/// <summary>
	/// 바인딩된 함수를 호출합니다.
	/// </summary>
	/// <param name="...InArgs"> 함수 매개변수 목록을 전달합니다. </param>
	/// <returns> 바인딩된 함수가 반환하는 값을 반환합니다. </returns>
	TRet Invoke(TArgs&&... InArgs)
	{
		return Invoker->Invoke(std::forward<TArgs>(InArgs)...);
	}

	/// <summary>
	/// 관리되지 않는 포인터에 대한 클래스 함수를 바인딩합니다.
	/// </summary>
	/// <typeparam name="TCaller"> 클래스 형식을 전달합니다. </typeparam>
	/// <param name="InRawPointer"> 개체 포인터를 전달합니다. </param>
	/// <param name="InMemberFunc"> 멤버 함수의 주소를 전달합니다. </param>
	/// <returns> 바인딩 된 함수 대리자가 반환됩니다. </returns>
	template<class TCaller>
	void BindRaw(TCaller* InRawPointer, TRet(TCaller::*InMemberFunc)(TArgs...))
	{
		if (Invoker != nullptr)
		{
			delete Invoker;
			Invoker = nullptr;
		}

		Invoker = new TCallableRaw(InRawPointer, InMemberFunc);
	}

	/// <summary>
	/// 참조 포인터에 대한 클래스 함수를 바인딩합니다.
	/// </summary>
	/// <typeparam name="TCaller"> 클래스 형식을 전달합니다. </typeparam>
	/// <param name="InRefPointer"> 참조 개체 포인터를 전달합니다. </param>
	/// <param name="InMemberFunc"> 멤버 함수의 주소를 전달합니다. </param>
	/// <returns> 바인딩 된 함수 대리자가 반환됩니다. </returns>
	template<TIsObject TCaller>
	void BindRef(TCaller* InRefPointer, TRet(TCaller::*InMemberFunc)(TArgs...))
	{
		if (Invoker != nullptr)
		{
			delete Invoker;
			Invoker = nullptr;
		}

		Invoker = new TCallableRef(InRefPointer, InMemberFunc);
	}

	/// <summary>
	/// 람다 함수를 바인딩합니다.
	/// </summary>
	/// <typeparam name="TLambda"> 람다 형식을 전달합니다. </typeparam>
	/// <param name="InLambda"> 람다 함수를 전달합니다. </param>
	/// <returns> 바인딩 된 함수 대리자가 반환됩니다. </returns>
	template<class TLambda>
	void BindLambda(TLambda InLambda)
	{
		if (Invoker != nullptr)
		{
			delete Invoker;
			Invoker = nullptr;
		}
		Invoker = new TCallableLambda(InLambda);
	}

	TFunction& operator =(TFunction&& rhs)
	{
		Invoker = rhs.Invoker;
		rhs.Invoker = nullptr;
		return *this;
	}

private:
	TCallableBase* Invoker;
};
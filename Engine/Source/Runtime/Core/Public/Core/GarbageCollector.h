// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <set>
#include "Core/CoreConcepts.h"

class SObject;

#pragma warning(disable: 4251)

/// <summary>
/// <see cref="Object"/> 클래스의 파생 클래스에 대한 레퍼런스를 수집합니다.
/// </summary>
class CORE_API GarbageCollector final
{
	friend class SObject;
	template<TIsNotPointer T>
	friend class TGCRoot;

	GarbageCollector() = delete;

private:
	static std::set<SObject*> gcroots;
	static std::set<SObject*> references;

protected:
	static void AddReference(SObject* reference);
	static void RemoveReference(SObject* reference);

	static void MoveReferenceToGCRoot(SObject* reference);
	static void RemoveReferenceFromGCRoot(SObject* reference);

public:
	/// <summary>
	/// 참조되지 않은 모든 레퍼런스를 수집합니다.
	/// </summary>
	static void Collect();

private:
	static void MarkSingleGCRoot(std::set<SObject*>& unmarked, SObject* gcroot);
};

/// <summary>
/// <see cref="Object"/> 클래스의 파생 클래스에 대한 레퍼런스를 수집합니다.
/// </summary>
using GC = GarbageCollector;
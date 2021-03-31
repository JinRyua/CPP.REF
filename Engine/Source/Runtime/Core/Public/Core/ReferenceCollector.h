// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <set>

class SObject;

#pragma warning(disable: 4251)

/// <summary>
/// <see cref="Object"/> 클래스의 파생 클래스에 대한 레퍼런스를 수집합니다.
/// </summary>
class CORE_API ReferenceCollector final
{
	friend class SObject;

	ReferenceCollector() = delete;

private:
	static std::set<SObject*> references_gen[2];

protected:
	static void AddReference(SObject* reference);
	static void RemoveReference(SObject* reference);

public:
	/// <summary>
	/// 참조되지 않은 모든 레퍼런스를 수집합니다.
	/// </summary>
	/// <param name="generation"> 수집할 세대 정보를 전달합니다. 전달된 세대보다 낮은 세대가 모두 회수됩니다. </param>
	static void Collect(size_t generation = 1);

private:
	static void CollectSingleGen(size_t generation);
};
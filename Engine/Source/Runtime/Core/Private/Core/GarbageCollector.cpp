// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/GarbageCollector.h"

#include <queue>
#include "Core/Object.h"
#include "Core/Type.h"
#include "Reflection/Field.h"

using namespace std;

set<SObject*> GC::gcroots;
set<SObject*> GC::references;

void GC::AddReference(SObject* reference)
{
	references.emplace(reference);
}

void GC::RemoveReference(SObject* reference)
{
	references.erase(reference);
}

void GC::MoveReferenceToGCRoot(SObject* reference)
{
	if (auto it = references.find(reference); it != references.end())
	{
		references.erase(it);
	}
	gcroots.emplace(reference);
}

void GC::RemoveReferenceFromGCRoot(SObject* reference)
{
	if (auto it = gcroots.find(reference); it != gcroots.end())
	{
		gcroots.erase(it);
		delete *it;
	}

	// 루트가 하나도 없을 경우
	if (gcroots.size() == 0)
	{
		// 모든 레퍼런스를 수집합니다.
		Collect();
	}
}

void GC::Collect()
{
	set<SObject*> unmarked = references;

	// GC루트에서 파생된 모든 오브젝트를 마크합니다.
	for (SObject* gcroot : gcroots)
	{
		MarkSingleGCRoot(unmarked, gcroot);
	}

	// 마크되지 않은 개체를 지웁니다.
	for (auto& it : unmarked)
	{
		delete it;
		references.erase(it);
	}
}

void GC::MarkSingleGCRoot(set<SObject*>& unmarked, SObject* gcroot)
{
	queue<SObject*> markqueue;
	markqueue.emplace(gcroot);

	while (!markqueue.empty())
	{
		gcroot = markqueue.front();
		markqueue.pop();

		span<SField* const> fields = gcroot->GetType()->GetFields();
		for (SField* field : fields)
		{
			// SObject 형식이 아닙니다.
			if (field == nullptr)
			{
				continue;
			}

			SObject* fieldObj = field->GetValue(gcroot);
			// 이 필드는 비어있습니다.
			if (fieldObj == nullptr)
			{
				continue;
			}

			auto it = unmarked.find(fieldObj);
			// 이 필드의 개체는 이미 마크되었습니다.
			if (it == unmarked.end())
			{
				continue;
			}

			// 개체를 마크하고, 다음 큐에 넣습니다.
			unmarked.erase(fieldObj);
			markqueue.push(fieldObj);
		}
	}
}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/ReferenceCollector.h"

#include "Core/Object.h"
#include "Core/Type.h"

using namespace std;

set<SObject*> ReferenceCollector::references_gen[2];

void ReferenceCollector::AddReference(SObject* reference)
{
	references_gen[0].emplace(reference);
}

void ReferenceCollector::RemoveReference(SObject* reference)
{
	references_gen[0].erase(reference);
}

void ReferenceCollector::Collect(size_t generation)
{
	for (size_t i = 0; i < generation; ++i)
	{
		CollectSingleGen(i);
	}

	references_gen[1].insert(references_gen[0].begin(), references_gen[0].end());
	references_gen[0].clear();
}

void ReferenceCollector::CollectSingleGen(size_t generation)
{
	list<SObject*> removes;

	for (auto& item : references_gen[generation])
	{
		size_t rc = item->GetReferenceCount();
		if (rc == generation)
		{
			removes.emplace_back(item);
		}
	}

	for (auto& item : removes)
	{
		references_gen[generation].erase(item);
		delete item;
	}
}
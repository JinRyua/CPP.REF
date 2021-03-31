// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

class SObject;

struct CORE_API WeakReferences
{
	friend class SObject;

private:
	size_t weakReferences;
	bool bValid : 1;

public:
	WeakReferences();
	~WeakReferences();

	void AddWeakRef();
	void ReleaseWeak();
	void AddWeakRefInterlocked();
	void ReleaseWeakInterlocked();

	bool IsValid() const;

private:
	void Invalidate();
};
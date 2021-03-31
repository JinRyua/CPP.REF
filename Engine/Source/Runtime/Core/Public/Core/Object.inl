// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

template<TIsNotPointer O, TIsNotPointer T> requires TIsBaseOf<O, SObject> && TIsBaseOf<T, SObject>
inline O* SObject::Cast(T* ptr)
{
	return dynamic_cast<O*>(ptr);
}

template<TIsNotPointer O, TIsNotPointer T> requires TIsBaseOf<O, SObject> && TIsBaseOf<T, SObject>
inline const O* SObject::Cast(const T* ptr)
{
	return dynamic_cast<const O*>(ptr);
}
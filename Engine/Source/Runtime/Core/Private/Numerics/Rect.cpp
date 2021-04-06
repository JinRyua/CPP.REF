// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Numerics/Rect.h"

#include "Numerics/Ray2.h"
#include "HashHelper.h"
#include "Core/String.h"
#include "Exception/IndexOutOfRangeException.h"

using namespace std;

Rect::Rect()
{

}

Rect::Rect(const Vector2& min, const Vector2& max)
{
	Min = min;
	Max = max;
}

Rect::Rect(const Rect& copy)
{
	Min = copy.Min;
	Max = copy.Max;
}

bool Rect::Equals(const Rect& rh) const
{
	return *this == rh;
}

bool Rect::NearlyEquals(const Rect& rh, float epsilon) const
{
	return Min.NearlyEquals(rh.Min, epsilon)
		&& Max.NearlyEquals(rh.Max, epsilon);
}

size_t Rect::GetHashCode() const
{
	return Min.GetHashCode() ^ Max.GetHashCode();
}

SString* Rect::ToString() const
{
	return SString::Format(
		"{{Min: {0}, Max: {1}, [{2} * {3}]}}"_s,
		Min,
		Max,
		GetWidth(),
		GetHeight()
	);
}

Vector2 Rect::GetCenter() const
{
	return (Min + Max) * 0.5f;
}

float Rect::GetWidth() const
{
	return Max.X - Min.X;
}

float Rect::GetHeight() const
{
	return Max.Y - Min.Y;
}

Vector2 Rect::GetExtent() const
{
	return { GetWidth(), GetHeight() };
}

float Rect::GetSize() const
{
	return GetWidth() * GetHeight();
}
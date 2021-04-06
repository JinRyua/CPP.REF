// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Numerics/Ray2.h"

#include "HashHelper.h"
#include "Core/String.h"
#include "Numerics/Rect.h"

using namespace std;

Ray2::Ray2()
{

}

Ray2::Ray2(const Vector2& origin, const Vector2& direction, optional<float> distance)
{
	Origin = origin;
	Direction = direction;
	Distance = distance;
}

Ray2::Ray2(const Ray2& copy)
{
	Origin = copy.Origin;
	Direction = copy.Direction;
	Distance = copy.Distance;
}

bool Ray2::Equals(const Ray2& rh) const
{
	return Origin == rh.Origin
		&& Direction == rh.Direction
		&& Distance == rh.Distance;
}

bool Ray2::NearlyEquals(const Ray2& rh, float epsilon) const
{
	return Origin.NearlyEquals(rh.Origin, epsilon)
		&& Direction.NearlyEquals(rh.Direction, epsilon)
		&& (Distance.has_value() == rh.Distance.has_value() && abs(Distance.value() - rh.Distance.value()) <= epsilon);
}

size_t Ray2::GetHashCode() const
{
	return Origin.GetHashCode()
		 ^ Direction.GetHashCode()
		 ^ (Distance.has_value() ? HashHelper::GetHashCode(Distance.value()) : 0);
}

SString* Ray2::ToString() const
{
	SString* dist = Distance.has_value() ? SString::Format("{0}"_s, Distance.value()) : "Inf"_s;
	return SString::Format(
		"{{Origin: {0}, Direction: {1}, Distance: {2}}}"_s,
		Origin,
		Direction,
		dist
	);
}

Vector2 Ray2::GetPoint(float distance) const
{
	return Origin + Direction * distance;
}

Vector2 Ray2::GetEndPoint() const
{
	if (Distance.has_value())
	{
		return GetPoint(Distance.value());
	}
	else
	{
		return Direction * std::numeric_limits<float>::infinity();
	}
}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Numerics/ObjectOrientedCube.h"

#include "Core/String.h"

using namespace std;

ObjectOrientedCube::ObjectOrientedCube()
{

}

ObjectOrientedCube::ObjectOrientedCube(const Vector3& center, const Vector3& extent, const Quaternion& rotation)
{
	Center = center;
	Extent = extent;
	Rotation = rotation;
}

ObjectOrientedCube::ObjectOrientedCube(const ObjectOrientedCube& copy)
{
	Center = copy.Center;
	Extent = copy.Extent;
	Rotation = copy.Rotation;
}

bool ObjectOrientedCube::Equals(const ObjectOrientedCube& rh) const
{
	return *this == rh;
}

bool ObjectOrientedCube::NearlyEquals(const ObjectOrientedCube& rh, float epsilon) const
{
	return Center.NearlyEquals(rh.Center, epsilon)
		&& Extent.NearlyEquals(rh.Extent, epsilon)
		&& Rotation.NearlyEquals(rh.Rotation, epsilon);
}

size_t ObjectOrientedCube::GetHashCode() const
{
	return Center.GetHashCode() ^ Extent.GetHashCode() ^ Rotation.GetHashCode();
}

SString* ObjectOrientedCube::ToString() const
{
	return SString::Format(
		"{{Center: {0}, Extent: {1}, Rotation: {2}}}"_s,
		Center,
		Extent,
		Rotation
	);
}

array<Vector3, 8> ObjectOrientedCube::CalcVertices() const
{
	float Signs[2] = { +1, -1 };

	array<Vector3, 8> verts;
	int index = 0;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				verts[index++] = Center + Signs[i] * GetAxisX() * Extent.X + Signs[j] * GetAxisY() * Extent.Y + Signs[k] * GetAxisZ() * Extent.Z;
			}
		}
	}

	return verts;
}

Vector3 ObjectOrientedCube::GetAxisX() const
{
	return Rotation.RotateVector(Vector3::AxisX);
}

Vector3 ObjectOrientedCube::GetAxisY() const
{
	return Rotation.RotateVector(Vector3::AxisY);
}

Vector3 ObjectOrientedCube::GetAxisZ() const
{
	return Rotation.RotateVector(Vector3::AxisZ);
}
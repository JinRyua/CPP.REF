// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Numerics/Vector2.h"

#include "HashHelper.h"
#include "Exception/IndexOutOfRangeException.h"
#include "Numerics/Rect.h"
#include "Mathematics/Math.h"
#include "Core/String.h"

using namespace std;

const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);

Vector2::Vector2()
{

}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::Vector2(float splat)
{
	X = splat;
	Y = splat;
}

Vector2::Vector2(const Vector2& copy)
{
	X = copy.X;
	Y = copy.Y;
}

bool Vector2::Equals(const Vector2& rh) const
{
	return (*this) == rh;
}

bool Vector2::NearlyEquals(const Vector2& rh, float epsilon) const
{
	return abs(X - rh.X) <= epsilon
		&& abs(Y - rh.Y) <= epsilon;
}

size_t Vector2::GetHashCode() const
{
	return HashHelper::GetHashCode(X)
		 ^ HashHelper::GetHashCode(Y);
}

SString* Vector2::ToString() const
{
	return SString::Format("{{{0}, {1}}}"_s, X, Y);
}

float Vector2::GetComponentOrDefault(size_t index) const
{
	if (!Contains(index))
	{
		return 0;
	}

	const float* ptr = &X;
	return ptr[index];
}

bool Vector2::Contains(size_t index) const
{
	return index < GetCount();
}

Vector2 Vector2::GetClampedToMaxLength(float inMaxLength) const
{
	if (inMaxLength < Math::SmallNumber<>)
	{
		return Vector2::Zero;
	}

	const float VSq = GetLengthSq();
	// If vector length is over than max length,
	// clamp it to max length.
	if (VSq > Math::Square(inMaxLength))
	{
		float scale = inMaxLength * Math::InvSqrt(VSq);
		return *this * scale;
	}
	else
	{
		return *this;
	}
}

float Vector2::GetLengthSq() const
{
	return X * X + Y * Y;
}

float Vector2::GetLength() const
{
	return Math::Sqrt(GetLengthSq());
}

Vector2 Vector2::GetNormalized() const
{
	return (*this) / GetLength();
}

Vector2 Vector2::GetDirection() const
{
	return GetNormalized();
}

void Vector2::SetDirection(const Vector2& value)
{
	(*this) = value * GetLength();
}

const float& Vector2::operator [](size_t index) const
{
	if (!Contains(index))
	{
		throw new SIndexOutOfRangeException();
	}

	const float* ptr = &X;
	return ptr[index];
}

float& Vector2::operator [](size_t index)
{
	if (!Contains(index))
	{
		throw new SIndexOutOfRangeException();
	}

	float* ptr = &X;
	return ptr[index];
}

Vector2 Vector2::operator -() const
{
	return Vector2(-X, -Y);
}

Vector2 Vector2::operator +(const Vector2& value) const
{
	return Vector2(X + value.X, Y + value.Y);
}

Vector2 Vector2::operator -(const Vector2& value) const
{
	return Vector2(X - value.X, Y - value.Y);
}

Vector2 Vector2::operator *(const Vector2& value) const
{
	return Vector2(X * value.X, Y * value.Y);
}

Vector2 Vector2::operator /(const Vector2& value) const
{
	return Vector2(X / value.X, Y / value.Y);
}

float Vector2::operator |(const Vector2& value) const
{
	return DotProduct(*this, value);
}

Vector2& Vector2::operator +=(const Vector2& right)
{
	X += right.X;
	Y += right.Y;
	return *this;
}

Vector2& Vector2::operator -=(const Vector2& right)
{
	X -= right.X;
	Y -= right.Y;
	return *this;
}

Vector2& Vector2::operator *=(const Vector2& right)
{
	X *= right.X;
	Y *= right.Y;
	return *this;
}

Vector2& Vector2::operator /=(const Vector2& right)
{
	X /= right.X;
	Y /= right.Y;
	return *this;
}

float Vector2::DistanceSq(const Vector2& left, const Vector2& right)
{
	return (right - left).GetLengthSq();
}

float Vector2::Distance(const Vector2& left, const Vector2& right)
{
	return (right - left).GetLength();
}

float Vector2::DotProduct(const Vector2& left, const Vector2& right)
{
	return left.X * right.X + left.Y * right.Y;
}

Vector2 Vector2::Min(const Vector2& lh, const Vector2& rh)
{
	return { Math::Min(lh.X, rh.X), Math::Min(lh.Y, rh.Y) };
}

Vector2 Vector2::Max(const Vector2& lh, const Vector2& rh)
{
	return { Math::Max(lh.X, rh.X), Math::Max(lh.Y, rh.Y) };
}

Vector2 operator +(float left, const Vector2& right)
{
	return Vector2(left) + right;
}

Vector2 operator -(float left, const Vector2& right)
{
	return Vector2(left) - right;
}

Vector2 operator *(float left, const Vector2& right)
{
	return Vector2(left) * right;
}

Vector2 operator /(float left, const Vector2& right)
{
	return Vector2(left) / right;
}
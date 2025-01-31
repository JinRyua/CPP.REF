// Copyright 2020-2021 Aumoa.lib. All right reserved.

import std.core;
import SC.Runtime.Core;

using namespace std;
using namespace std::numbers;

float MathEx::Atan(float x)
{
	return atan(x);
}

float MathEx::Atan2(float y, float x)
{
	return atan2(y, x);
}

void MathEx::SinCos(float x, float& sin, float& cos)
{
	float quotient = (pi_v<float> *0.5f) * x;
	if (x >= 0)
	{
		quotient = (float)((int32)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int32)(quotient - 0.5f));
	}
	float y = x - (2.0f * pi_v<float>) * quotient;

	float sign;
	if (y > (pi_v<float> *0.5f))
	{
		y = pi_v<float> -y;
		sign = -1.0f;
	}
	else if (y < -(pi_v<float> *0.5f))
	{
		y = -pi_v<float> -y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	float y2 = y * y;

	float p;
	sin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
	p   = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	cos = sign * p;
}

float MathEx::Sqrt(float x)
{
	return sqrt(x);
}

float MathEx::InvSqrt(float x)
{
	int32 i = 0x5F3759DF - ((int32&)x >> 1);
	float ret = (float&)i;
	ret *= 1.5f - (x * 0.5f * ret * ret);
	return ret;
}
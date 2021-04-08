// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Time/StepTimer.h"
SCLASS_BODY_IMPL(SStepTimer);

#undef interface
#include <Windows.h>
#include "Exception/NotSupportedException.h"
#include "Mathematics/Math.h"
#include "Core/String.h"

SStepTimer::SStepTimer() : Super()
	, frequency(QueryPerformanceFrequency())
	, standard(0)

	, lasttime(0)
	, maxDelta(0)
	
	, elapsedTicks(0)
	, totalTicks(0)
	, leftOverTicks(0)

	, frameCount(0)
	, framesPerSecond(0)
	, framesThisSecond(0)
	, secondCounter(0)

	, targetElapsedTicks(0)
{
	standard = QueryPerformanceCounter();
}

SStepTimer::~SStepTimer()
{

}

SString* SStepTimer::ToString() const
{
	if (bPrintSimplyScope)
	{
		return SString::Format("{0}"_s, (Milliseconds)GetTotalSeconds());
	}
	else
	{
		int32 length = (int32)GetTotalSeconds().GetValue();
		bool under = false;
		std::wostringstream builder;

		if (length >= 3600)
		{
			builder << length / 3600 << L"H ";
			length %= 3600;
			under = true;
		}

		if (under || length >= 60)
		{
			builder << length / 60 << L"M ";
			length %= 60;
			under = true;
		}

		builder << length << L" Seconds (" << GetTicksPerSecond() << L" FPS)";

		return new SString(builder.str());
	}
}

void SStepTimer::ResetElapsedTime()
{
	lasttime = GetStandardPerformanceCounter();
	framesPerSecond = 0;
	framesThisSecond = 0;
	secondCounter = 0;
}

void SStepTimer::Tick()
{
	auto currentTime = GetStandardPerformanceCounter();
	auto timeDelta = currentTime - lasttime;

	lasttime = currentTime;
	secondCounter += timeDelta;

	if (maxDelta != 0 && timeDelta > maxDelta)
	{
		timeDelta = maxDelta;
	}

	const bool bFixedTimeStep = IsFixedTimeStep();
	uint32 lastFrameCount = frameCount;

	if (bFixedTimeStep)
	{
		if (Math::Abs((int64)(timeDelta - targetElapsedTicks)) < (int64)GetTicksPerSecond() / 4000)
		{
			timeDelta = targetElapsedTicks;
		}

		leftOverTicks += timeDelta;

		if (leftOverTicks >= targetElapsedTicks)
		{
			elapsedTicks = targetElapsedTicks;
			totalTicks += targetElapsedTicks;
			leftOverTicks -= targetElapsedTicks;
			frameCount += 1;

			StepTimerCallback.Broadcast(this);
		}
	}
	else
	{
		elapsedTicks = timeDelta;
		totalTicks += timeDelta;
		leftOverTicks = 0;
		frameCount += 1;

		StepTimerCallback.Broadcast(this);
	}

	if (frameCount != lastFrameCount)
	{
		framesThisSecond += 1;
	}

	if (secondCounter >= (uint64)frequency)
	{
		framesPerSecond = framesThisSecond;
		framesThisSecond = 0;
		secondCounter %= frequency;
	}
}

uint64 SStepTimer::SecondsToTicks(Seconds value) const
{
	return (uint64)(value.GetValue() * (float)frequency);
}

Seconds SStepTimer::TicksToSeconds(uint64 value) const
{
	return (float)value / (float)frequency;
}

uint64 SStepTimer::QueryPerformanceFrequency()
{
	uint64 freq;
	if (!::QueryPerformanceFrequency((LARGE_INTEGER*)&freq))
	{
		throw new SNotSupportedException("Performance counter is not supported."_s);
	}
	return freq;
}

uint64 SStepTimer::QueryPerformanceCounter()
{
	uint64 value;
	::QueryPerformanceCounter((LARGE_INTEGER*)&value);
	return value;
}
// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

#include "Delegates/TMulticastDelegate.h"
#include "Duration.h"

/// <summary>
/// 간단한 시간 측정 기능을 제공하는 클래스입니다.
/// </summary>
SCLASS(SStepTimer) class CORE_API SStepTimer : virtual public SObject
{
	SCLASS_BODY(SStepTimer)

public:
	/// <summary>
	/// 타이머 주기마다 호출되는 이벤트의 대리자 형식입니다.
	/// </summary>
	using StepTimerCallbackDelegate = TMulticastDelegate<void(SStepTimer*)>;

private:
	const uint64 frequency;
	uint64 standard;

	uint64 lasttime;
	uint64 maxDelta;

	uint64 elapsedTicks;
	uint64 totalTicks;
	uint64 leftOverTicks;

	uint32 frameCount;
	uint32 framesPerSecond;
	uint32 framesThisSecond;
	uint64 secondCounter;

	bool bPrintSimplyScope : 1;
	uint64 targetElapsedTicks;

public:
	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	SStepTimer();
	~SStepTimer() override;

	/// <summary>
	/// 간단한 설명을 텍스트 형식으로 가져옵니다.
	/// </summary>
	/// <returns> 생성된 텍스트 개체가 반환됩니다. </returns>
	SString* ToString() const override;

	/// <summary>
	/// 이전 프레임으로부터 흐른 시간을 초기화합니다.
	/// </summary>
	void ResetElapsedTime();

	/// <summary>
	/// 시간 값을 갱신합니다.
	/// </summary>
	void Tick();

	/// <summary>
	/// 타이머 주기마다 호출되는 이벤트입니다.
	/// </summary>
	StepTimerCallbackDelegate StepTimerCallback;

	/// <summary>
	/// 이전 프레임으로부터 흐른 시간을 틱 단위로 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	uint64 GetElapsedTicks() const { return elapsedTicks; }

	/// <summary>
	/// 이전 프레임으로부터 흐른 시간을 초 단위로 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Seconds GetElapsedSeconds() const { return TicksToSeconds(elapsedTicks); }

	/// <summary>
	/// 전체 흐른 시간을 틱 단위로 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	uint64 GetTotalTicks() const { return totalTicks; }

	/// <summary>
	/// 전체 흐른 시간을 초 단위로 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Seconds GetTotalSeconds() const { return TicksToSeconds(totalTicks); }

	/// <summary>
	/// 전체 프레임 수를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	uint64 GetTickCount() const { return frameCount; }

	/// <summary>
	/// 초당 프레임 수를 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	int32 GetTicksPerSecond() const { return (int32)framesPerSecond; }

	/// <summary>
	/// 이 타이머가 고정 틱 주기를 사용하는지 나타내는 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	bool IsFixedTimeStep() const { return targetElapsedTicks != 0; }

	/// <summary>
	/// 타이머가 고정 틱 주기를 사용할 경우, 고정 주기 틱 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	uint64 GetFixedTimeStepTicks() const { return targetElapsedTicks; }

	/// <summary>
	/// 타이머가 고정 틱 주기를 사용할 경우, 고정 주기 초 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Seconds GetFixedTiemStepSeconds() const { return TicksToSeconds(targetElapsedTicks); }

	/// <summary>
	/// 타이머가 고정 틱 주기를 사용하는지 나타내는 값을 설정합니다.
	/// </summary>
	/// <param name="value"> 설정할 틱 값을 전달합니다. 0일 경우 고정 주기를 사용하지 않습니다. </param>
	void SetFixedTimeStep(uint64 value) { targetElapsedTicks = value; }

	/// <summary>
	/// 타이머가 고정 틱 주기를 사용하는지 나타내는 값을 설정합니다.
	/// </summary>
	/// <param name="value"> 설정할 초 값을 전달합니다. 0일 경우 고정 주기를 사용하지 않습니다. </param>
	void SetFixedTimeStep(Seconds value) { targetElapsedTicks = SecondsToTicks(value); }

	/// <summary>
	/// 최대 틱 주기 변화량 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	uint64 GetMaxDeltaTicks() const { return maxDelta; }

	/// <summary>
	/// 최대 틱 주기 변화량 값을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetMaxDeltaTicks(uint64 value) { maxDelta = value; }

	/// <summary>
	/// 최대 틱 주기 변화량 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	Seconds GetMaxDeltaSeconds() const { return TicksToSeconds(maxDelta); }

	/// <summary>
	/// 최대 틱 주기 변화량 값을 설정합니다.
	/// </summary>
	/// <param name="value"> 값을 전달합니다. </param>
	void SetMaxDeltaSeconds(Seconds value) { maxDelta = SecondsToTicks(value); }

private:
	uint64 GetStandardPerformanceCounter() const { return QueryPerformanceCounter() - standard; }
	uint64 SecondsToTicks(Seconds value) const;
	Seconds TicksToSeconds(uint64 value) const;

private:
	static uint64 QueryPerformanceFrequency();
	static uint64 QueryPerformanceCounter();
};
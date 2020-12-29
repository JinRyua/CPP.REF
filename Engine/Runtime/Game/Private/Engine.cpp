﻿// Copyright 2020 Aumoa.lib. All right reserved.

#include "Engine.h"

#include "Application.h"
#include "GameInstance.h"
#include "RHI/IRHISwapChain.h"
#include "RHI/IRHIResource.h"
#include "Logging/LogVerbosity.h"
#include "Logging/LogMacros.h"
#include "SceneRendering/SceneRenderer.h"
#include "RHI/IRHICommandFence.h"
#include "RHI/IRHIImmediateCommandList.h"
#include "RHI/RHIResourceStates.h"
#include "RHI/IRHIRenderTargetView.h"
#include "RHI/IRHIDeferredCommandList.h"

#include "D3D12RHI/D3D12DeviceBundle.h"
//#include "VulkanRHI/VulkanDeviceBundle.h"

using namespace SC::Runtime::Core;
using namespace SC::Runtime::Game;
using namespace SC::Runtime::Game::RHI;
using namespace SC::Runtime::Game::D3D12RHI;
using namespace SC::Runtime::Game::Logging;
using namespace SC::Runtime::Game::SceneRendering;
using namespace std;
using namespace std::chrono;

Engine* Engine::gEngine = nullptr;

Engine::Engine() : Super()
	, LogEngine(ELogVerbosity::Verbose, nameof(LogEngine))
	, gameInstance(nullptr)

	, deviceBundle(nullptr)
	, immediateCommandList(nullptr)
	, swapChain(nullptr)

	, bPresent(false)
{

}

Engine::~Engine()
{
	// Waiting for all GPU tasks.
	autoFence->BeginFence();
}

void Engine::Initialize()
{
	if (gEngine != nullptr)
	{
		SE_LOG(LogEngine, Fatal, L"Engine duplication detected.");
		throw Exception("Unexpected exception.");
	}

	auto deviceBundle = NewObject<D3D12DeviceBundle>();
	this->deviceBundle = deviceBundle.Get();
	rhiBundles.push_back(deviceBundle);

	ForEachBundles([](auto* bundle) { bundle->InitializeBundle(); });

	autoFence = deviceBundle->CreateCommandFence();
	immediateCommandList = deviceBundle->GetImmediateCommandList().Get();
	swapChain = deviceBundle->GetSwapChain().Get();

	sceneRenderer = NewObject<SceneRenderer>(this->deviceBundle);

	gEngine = this;
	prev_tick = steady_clock::now();
}

void Engine::PostInitialize()
{
	gameInstance = GApplication.GetGameInstance();
}

void Engine::Tick()
{
	auto curr_tick = steady_clock::now();
	auto delta = curr_tick - prev_tick;
	prev_tick = curr_tick;

	gameInstance->Tick(delta);

	TRefPtr<IRHISwapChain> swapChain = deviceBundle->GetSwapChain();

	autoFence->BeginFence();

	IRHIResource* target = swapChain->GetBuffer(swapChain->CurrentBackBufferIndex).Get();

	// TODO: SceneRenderer
	sceneRenderer->BeginRender();
	sceneRenderer->EndRender();
	immediateCommandList->ExecuteCommandList(sceneRenderer->CommandList);

	immediateCommandList->BeginCommand();
	immediateCommandList->ResourceTransition(target, RHIResourceStates::PRESENT, RHIResourceStates::COPY_DEST);
	immediateCommandList->CopyResource(target, sceneRenderer->FinalColor);
	immediateCommandList->ResourceTransition(target, RHIResourceStates::COPY_DEST, RHIResourceStates::PRESENT);
	immediateCommandList->EndCommand();
	immediateCommandList->Flush();

	swapChain->Present();

	autoFence->EndFence(immediateCommandList);
}

IRHIDeviceBundle* Engine::DeviceBundle_get() const
{
	return deviceBundle;
}

Engine* Engine::GetInstance()
{
	return gEngine;
}

void Engine::ForEachBundles(function<void(IRHIBundle*)> action)
{
	for (auto& bundle : rhiBundles)
	{
		action(bundle.Get());
	}
}
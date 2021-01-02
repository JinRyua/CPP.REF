﻿// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "IRHIBundle.h"

#include <span>

interface IRHISwapChain;
interface IRHIImmediateCommandList;
interface IRHICommandFence;
interface IRHIRenderTargetView;
interface IRHIResource;
interface IRHIDeferredCommandList;
interface IRHIFence;

enum class ERHITextureFormat;
enum class ERHIResourceFlags;
enum class ERHIResourceStates;

class RHIShaderLibrary;
class RHIResourceGC;
struct RHIVertex;

interface IRHIDeviceBundle : virtual public Object, virtual public IRHIBundle
{
	virtual TRefPtr<IRHISwapChain> GetSwapChain() const = 0;
	virtual IRHIImmediateCommandList* GetImmediateCommandList() const = 0;
	virtual RHIShaderLibrary* GetShaderLibrary() const = 0;
	virtual RHIResourceGC* GetResourceGC() const = 0;

	virtual TRefPtr<IRHICommandFence> CreateCommandFence() = 0;
	virtual TRefPtr<IRHIRenderTargetView> CreateRenderTargetView(IRHIResource* resource) = 0;
	virtual TRefPtr<IRHIResource> CreateTexture2D(ERHITextureFormat format, int32 width, int32 height, ERHIResourceStates initialStates, ERHIResourceFlags flags) = 0;
	virtual TRefPtr<IRHIDeferredCommandList> CreateDeferredCommandList() = 0;
	virtual TRefPtr<IRHIFence> CreateFence() = 0;

	virtual TRefPtr<IRHIResource> CreateVertexBuffer(std::span<RHIVertex> vertices) = 0;
	virtual TRefPtr<IRHIResource> CreateIndexBuffer(std::span<uint32> indices) = 0;
};
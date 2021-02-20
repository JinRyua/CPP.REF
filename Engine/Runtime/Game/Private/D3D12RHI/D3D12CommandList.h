﻿// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "RHI/IRHICommandList.h"

#include "D3D12Minimal.h"

class D3D12OnlineDescriptorPatch;

class D3D12CommandList : virtual public Object, virtual public IRHICommandList
{
public:
	using Super = Object;

private:
	std::vector<D3D12_RESOURCE_BARRIER> pendingBarriers;
	bool bHasBegunCommand : 1;

	ID3D12RootSignature* currentRS;
	D3D12OnlineDescriptorPatch* currentPatch;

public:
	D3D12CommandList();
	~D3D12CommandList() override;

	virtual void BeginCommand();
	virtual void EndCommand();

	virtual void SetRenderTargets(size_t count, IRHIRenderTargetView* rtv[], IRHIDepthStencilView* dsv);
	virtual void ClearRenderTargetView(IRHIRenderTargetView* rtv);
	virtual void ResourceTransition(IRHIResource* resource, ERHIResourceStates beforeState, ERHIResourceStates afterState, size_t subresourceIndex = 0);
	virtual void CopyResource(IRHIResource* target, IRHIResource* source);
	virtual void SetShader(IRHIShader* shader);
	virtual void SetPrimitiveTopology(ERHIPrimitiveTopology primitiveTopology);
	virtual void SetScissorRects(const Rect& scissorRect);
	virtual void SetViewports(const RHIViewport& viewport);
	virtual void DrawMesh(const RHIMeshDrawCommand& command);
	virtual void SetGraphicsRootConstantBufferView(uint32 inParamIndex, uint64 inVirtualAddress);
	virtual void ClearDepthStencilView(IRHIDepthStencilView* dsv, std::optional<float> depth, std::optional<uint8> stencil);
	virtual void SetGraphicsRootShaderResourceView(uint32 inRootParameterIndex, IRHIShaderResourceView* inSRV);
	virtual void CopyBufferRegion(IRHIResource* inDstBuffer, uint64 inDstLocation, IRHIResource* inSrcBuffer, uint64 inSrcLocation, uint64 inNumBytes);
	virtual void SetGraphicsRoot32BitConstants(uint32 inParamIndex, const uint32* inBytes, size_t inNum32Bits, size_t location);
	virtual void SetGraphicsRootShaderResource(uint32 inParamIndex, uint64 inVirtualAddress);
	virtual void BeginRenderTarget(IRHIRenderTarget* renderTarget);
	virtual void EndRenderTarget(IRHIRenderTarget* renderTarget);
	virtual void SetShaderDescriptorPatch(IRHIOnlineDescriptorPatch* inPatch);

	virtual bool HasBegunCommand_get() const;

	vs_property_get(ID3D12GraphicsCommandList4*, CommandList);
	virtual ID3D12GraphicsCommandList4* CommandList_get() = 0;

private:
	void ConsumePendingDeferredCommands();
};
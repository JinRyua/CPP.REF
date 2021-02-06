﻿// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "RHI/IRHIShader.h"

#include "D3D12Minimal.h"

class D3D12Shader : virtual public Object, virtual public IRHIShader
{
public:
	using Super = Object;
	using This = D3D12Shader;

private:
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;

	bool bShaderInitialized : 1;
	size_t shaderTypeHash;

public:
	D3D12Shader(ID3D12RootSignature* inRootSignature, ID3D12PipelineState* inPipelineState);
	~D3D12Shader();

	vs_property_get(ID3D12RootSignature*, RootSignature);
	ID3D12RootSignature* RootSignature_get() const;
	vs_property_get(ID3D12PipelineState*, PipelineState);
	ID3D12PipelineState* PipelineState_get() const;
};
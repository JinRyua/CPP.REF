// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Internal.h"

import SC.Runtime.RenderCore;
import std.core;
import SC.Runtime.Core;

using namespace std;

using enum ELogVerbosity;

RHIShader::RHIShader(RHIDevice* device) : Super(device)
{
}

RHIShader::~RHIShader()
{
}

void RHIShader::Compile(RHIVertexFactory* vertexDeclaration)
{
	span<uint8 const> vsBytecode = CompileVS();
	span<uint8 const> psBytecode = CompilePS();
	ID3D12Device* dev = GetDevice()->GetDevice();

	vector<RHIShaderParameterElement> shaderParameters = GetShaderParameterDeclaration();
	vector<D3D12_ROOT_PARAMETER> rootParameters;

	for (size_t i = 0; i < shaderParameters.size(); ++i)
	{
		RHIShaderParameterElement& myParam = shaderParameters[i];
		switch (myParam.Type)
		{
		case ERHIShaderParameterType::ParameterCollection:
		case ERHIShaderParameterType::ParameterCollection_CameraConstants:
			rootParameters.emplace_back() =
			{
				.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV,
				.Descriptor =
				{
					.ShaderRegister = myParam.ParameterCollection.ShaderRegister,
					.RegisterSpace = myParam.ParameterCollection.RegisterSpace
				}
			};
			break;
		default:
			LogSystem::Log(LogRHI, Error, L"Shader parameter type({}) is corrupted.", (int32)myParam.Type);
			rootParameters.emplace_back();
			break;
		}
	}

	D3D12_ROOT_SIGNATURE_DESC rsd =
	{
		.NumParameters = (UINT)rootParameters.size(),
		.pParameters = rootParameters.empty() ? nullptr : rootParameters.data(),
		.NumStaticSamplers = 0,
		.pStaticSamplers = nullptr,
		.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
		| D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS
		| D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS
		| D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
		| D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS
		| D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS
	};

	ComPtr<ID3DBlob> blob, error;
	HRESULT hr = D3D12SerializeRootSignature(&rsd, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &error);
	if (FAILED(hr))
	{
		// Compile error detected. Print error message and throw fatal exception.
		if (error)
		{
			LogSystem::Log(LogRHI, Fatal,
				L"Could not compile root signature with follow reason:\n{}",
				StringUtils::AsUnicode((const char*)error->GetBufferPointer()));
		}
		else
		{
			HR(LogRHI, hr);
		}
	}

	HR(LogRHI, dev->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&_rs)));

	// Make vertex declaration to input element.
	vector<RHIVertexElement> declaration = vertexDeclaration->GetVertexDeclaration();
	vector<D3D12_INPUT_ELEMENT_DESC> inputElements(declaration.size());

	for (size_t i = 0; i < inputElements.size(); ++i)
	{
		auto& element = declaration[i];

		inputElements[i] =
		{
			.SemanticName = element.SemanticName.c_str(),
			.SemanticIndex = element.SemanticIndex,
			.Format = (DXGI_FORMAT)element.Format,
			.InputSlot = element.InputSlot,
			.AlignedByteOffset = element.AlignedByteOffset,
			.InputSlotClass = (D3D12_INPUT_CLASSIFICATION)element.InputSlotClass,
			.InstanceDataStepRate = 0
		};
	}

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psd =
	{
		.pRootSignature = _rs.Get(),
		.VS =
		{
			.pShaderBytecode = vsBytecode.data(),
			.BytecodeLength = vsBytecode.size()
		},
		.PS =
		{
			.pShaderBytecode = psBytecode.data(),
			.BytecodeLength = psBytecode.size()
		},
		.BlendState =
		{
			.AlphaToCoverageEnable = FALSE,
			.IndependentBlendEnable = FALSE,
			.RenderTarget =
			{
				// [0]
				{
					.BlendEnable = FALSE,
					.LogicOpEnable = FALSE,
					.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL
				}
			}
		},
		.SampleMask = 0xFFFFFFFF,
		.RasterizerState =
		{
			.FillMode = D3D12_FILL_MODE_SOLID,
			.CullMode = D3D12_CULL_MODE_NONE,
		},
		.DepthStencilState =
		{
			.DepthEnable = TRUE,
			.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
			.DepthFunc = D3D12_COMPARISON_FUNC_LESS,
			.StencilEnable = FALSE
		},
		.InputLayout =
		{
			.pInputElementDescs = inputElements.empty() ? nullptr : inputElements.data(),
			.NumElements = (UINT)inputElements.size()
		},
		.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
		.NumRenderTargets = 1,
		.RTVFormats =
		{
			// [0]
			DXGI_FORMAT_B8G8R8A8_UNORM
		},
		//.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT,
		.SampleDesc = { 1, 0 },
	};

	HR(LogRHI, dev->CreateGraphicsPipelineState(&psd, IID_PPV_ARGS(&_ps)));
}
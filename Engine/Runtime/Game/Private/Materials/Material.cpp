﻿// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Materials/Material.h"

#include "DirectX/DirectXCommon.h"
#include "DirectX/DirectXDeviceBundle.h"
#include "DirectX/DirectXDynamicBufferAllocator.h"
#include "DirectX/DirectXShaderResourceView.h"
#include "Shaders/ShaderTypes.h"

Material::Material(DirectXDeviceBundle* deviceBundle) : Super()
	, bMarkDirty(false)
	, deviceBundle(nullptr)
{
	SetMarkDirty(EMaterialDirtyMask::All);
	
	DirectXDynamicBufferAllocator* allocator = deviceBundle->GetOrCreateDynamicBufferAllocator(sizeof(ShaderTypes::Material));
	materialBuffer = NewObject<DirectXDynamicBuffer>(allocator);
	surfaceSRV = NewObject<DirectXShaderResourceView>(deviceBundle, 2);
}

Material::~Material()
{

}

void Material::SetMarkDirty(EMaterialDirtyMask inAddMask)
{
	Super::SetMarkDirty(inAddMask);

	if (!bMarkDirty)
	{
		bMarkDirty = true;
	}
}

void Material::ResolveDirtyState()
{
	D3D12_SHADER_RESOURCE_VIEW_DESC nullDesc = { };
	nullDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	nullDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	nullDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	nullDesc.Texture2D.MipLevels = 1;

	if (HasDirtyMark(EMaterialDirtyMask::RenderState))
	{
		ShaderTypes::Material mat = { Ambient, Diffuse, Specular, SpecExp };
		memcpy(materialBuffer->GetBufferPointer(), &mat, sizeof(mat));
	}

	if (HasDirtyMark(EMaterialDirtyMask::SurfaceTexture))
	{
		surfaceSRV->CreateShaderResourceView(0, DiffuseMap, DiffuseMap ? nullptr : &nullDesc);
		surfaceSRV->CreateShaderResourceView(1, NormalMap, NormalMap ? nullptr : &nullDesc);
	}

	Super::ResolveDirtyState();
	bMarkDirty = false;
}

DirectXShaderResourceView* Material::SurfaceTextureSRV_get() const
{
	return surfaceSRV.Get();
}
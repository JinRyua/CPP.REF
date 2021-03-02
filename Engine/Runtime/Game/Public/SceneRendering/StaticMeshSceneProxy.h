﻿// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "PrimitiveSceneProxy.h"

class StaticMeshComponent;
class StaticMesh;

class GAME_API StaticMeshSceneProxy : public PrimitiveSceneProxy
{
public:
	using Super = PrimitiveSceneProxy;
	using This = StaticMeshSceneProxy;

private:
	TWeakPtr<StaticMeshComponent> meshComponent;
	StaticMesh* staticMesh;
	AxisAlignedCube baseBoundingBox;
	AxisAlignedCube transformedBoundingBox;
	uint16 materialIndex;

	TRefPtr<MeshBatch> customBatch;

public:
	StaticMeshSceneProxy(StaticMeshComponent* inMeshComponent);
	~StaticMeshSceneProxy();

	void Update() override;
	void UpdateTransform() override;

	MeshBatch* GetMeshBatch() const override;
	const AxisAlignedCube* GetPrimitiveBoundingBox() const override;
	uint64 GetRaytracingAccelerationStructurePtr() const override;
};
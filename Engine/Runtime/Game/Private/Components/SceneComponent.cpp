﻿// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Components/SceneComponent.h"

#include "Logging/LogMacros.h"
#include "Diagnostics/ScopedCycleCounter.h"

DEFINE_STATS_GROUP(GSceneComponent);

using namespace std;

GSceneComponent::SceneAttachment::SceneAttachment()
	: AttachmentRoot(nullptr)
{

}

GSceneComponent::SceneAttachment::~SceneAttachment()
{

}

void GSceneComponent::SceneAttachment::Clear()
{
	AttachmentRoot = nullptr;
	SocketName = nullptr;
}

GSceneComponent::GSceneComponent() : Super()
	, transform(Transform::Identity)
	, worldTransform(Transform::Identity)
	, localToWorld(Transform::Identity)
	, mobility(EComponentMobility::Static)
	, dirtyMark(EComponentDirtyMask::All)
{

}

GSceneComponent::~GSceneComponent()
{

}

void GSceneComponent::UpdateChildTransforms()
{
	for (GSceneComponent* child : childComponents)
	{
		child->UpdateComponentToWorld();
	}
}

void GSceneComponent::UpdateComponentToWorld()
{
	QUICK_SCOPED_CYCLE_COUNTER(GSceneComponent, UpdateComponentToWorld);

	if (AttachParent == nullptr)
	{
		localToWorld = Transform::Identity;
		return;
	}

	if (AttachSocketName.IsValid)
	{
		localToWorld = AttachParent->GetSocketTransform(AttachSocketName);
	}
	else
	{
		localToWorld = AttachParent->ComponentTransform;
	}

	UpdateWorldTransform();
}

Transform GSceneComponent::GetSocketTransform(TRefPtr<String> socketName, EComponentTransformSpace space) const
{
	SE_LOG(LogSceneComponent, Error, L"GSceneComponent::GetSocketName() called. SceneComponent have not any sockets. Use override this function and provide correct socket transform.");

	switch (space)
	{
	case EComponentTransformSpace::World:
		return ComponentTransform;
	}

	return RelativeTransform;
}

bool GSceneComponent::MoveComponent(const Vector3& inMoveDelta, const Quaternion& inNewRotation, EComponentTransformSpace inSpace)
{
	Quaternion oldRotation = inSpace == EComponentTransformSpace::World ? ComponentRotation : Rotation;
	if (inMoveDelta.NearlyEquals(Vector3::Zero, Math::SmallNumber<>) && oldRotation.NearlyEquals(inNewRotation, Math::SmallNumber<>))
	{
		// MoveDelta and NewRotation is nearly equals to previous component transform.
		// Skip moving and return state indicating that be not moved.
		return false;
	}

	Vector3 relativeLocation;
	Quaternion relativeRotation;

	if (inSpace == EComponentTransformSpace::World && AttachParent != nullptr)
	{
		// Transform unit is only calculate from local space.
		// Therefore, will convert world space unit to local space unit and apply it.
		Vector3 newLocation = ComponentLocation + inMoveDelta;
		Quaternion newRotation = inNewRotation;

		auto worldTransform = Transform(newLocation, ComponentScale, newRotation);
		auto relativeTransform = worldTransform.GetRelativeTransform(AttachParent->GetSocketTransform(AttachSocketName));

		relativeLocation = relativeTransform.Translation;
		relativeRotation = relativeTransform.Rotation;
	}
	else
	{
		relativeLocation = Location + inMoveDelta;
		relativeRotation = inNewRotation;
	}

	transform.Translation = relativeLocation;
	transform.Rotation = relativeRotation;
	UpdateWorldTransform();

	return true;
}

void GSceneComponent::AttachToComponent(GSceneComponent* attachTo)
{
	AttachToSocket(attachTo, nullptr);
}

void GSceneComponent::AttachToSocket(GSceneComponent* attachTo, TRefPtr<String> socketName)
{
	if (attachTo == nullptr)
	{
		SE_LOG(LogSceneComponent, Warning, L"{0} is nullptr. First argument of AttachToComponent function must not be nullptr. Abort.", nameof(attachTo));
		return;
	}

	if (componentAttachment.AttachmentRoot == attachTo && componentAttachment.SocketName == socketName)
	{
		SE_LOG(LogSceneComponent, Verbose, L"Component is already attach to desired target. Abort.");
		return;
	}

	if (componentAttachment.AttachmentRoot != nullptr)
	{
		DetachFromComponent();
	}

	attachTo->childComponents.emplace_back(this);
	componentAttachment.AttachmentRoot = attachTo;
	componentAttachment.SocketName = socketName;

	UpdateComponentToWorld();
}

void GSceneComponent::DetachFromComponent()
{
	if (componentAttachment.AttachmentRoot == nullptr)
	{
		SE_LOG(LogSceneComponent, Verbose, L"Component is already detached from any components. Abort.");
		return;
	}

	auto it = find(childComponents.begin(), childComponents.end(), this);
	if (it == childComponents.end())
	{
		SE_LOG(LogSceneComponent, Error, L"Cannot found this component from child component list of parent component.");
	}
	else
	{
		childComponents.erase(it);
	}

	componentAttachment.AttachmentRoot = nullptr;
	componentAttachment.SocketName = nullptr;

	UpdateComponentToWorld();
}

void GSceneComponent::SetMarkDirty(EComponentDirtyMask inSetMasks)
{
	dirtyMark |= inSetMasks;
}

bool GSceneComponent::HasAnyDirtyMark() const
{
	return dirtyMark != EComponentDirtyMask::None;
}

bool GSceneComponent::HasDirtyMark(EComponentDirtyMask inMask) const
{
	return (dirtyMark & inMask) != EComponentDirtyMask::None;
}

void GSceneComponent::ResolveDirtyState()
{
	dirtyMark = EComponentDirtyMask::None;
}

GSceneComponent* GSceneComponent::AttachParent_get() const
{
	return componentAttachment.AttachmentRoot;
}

TRefPtr<String> GSceneComponent::AttachSocketName_get() const
{
	return componentAttachment.SocketName;
}

const vector<GSceneComponent*>& GSceneComponent::ChildComponents_get() const
{
	return childComponents;
}

Transform GSceneComponent::RelativeTransform_get() const
{
	return transform;
}

void GSceneComponent::RelativeTransform_set(Transform value)
{
	transform = value;
	UpdateWorldTransform();
}

Transform GSceneComponent::ComponentTransform_get() const
{
	return worldTransform;
}

Vector3 GSceneComponent::Location_get() const
{
	return transform.Translation;
}

void GSceneComponent::Location_set(Vector3 value)
{
	transform.Translation = value;
	UpdateWorldTransform();
}

Vector3 GSceneComponent::Scale_get() const
{
	return transform.Scale;
}

void GSceneComponent::Scale_set(Vector3 value)
{
	transform.Scale = value;
	UpdateWorldTransform();
}

Quaternion GSceneComponent::Rotation_get() const
{
	return transform.Rotation;
}

void GSceneComponent::Rotation_set(Quaternion value)
{
	transform.Rotation = value;
	UpdateWorldTransform();
}

void GSceneComponent::UpdateWorldTransform()
{
	if (HasBegunPlay && Mobility != EComponentMobility::Movable)
	{
		SE_LOG(LogSceneComponent, Error, L"SceneComponent has been try move but it is not movable mobility.");
	}

	if (AttachParent != nullptr)
	{
		worldTransform = Transform::Multiply(transform, localToWorld);
	}
	else
	{
		worldTransform = transform;
	}
	SetMarkDirty(EComponentDirtyMask::TransformUpdated);

	UpdateChildTransforms();
}
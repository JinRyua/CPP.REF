﻿// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Components/ActorComponent.h"

#include "Logging/LogMacros.h"
#include "Framework/Actor.h"

using namespace std;

GActorComponent::ComponentTickFunction::ComponentTickFunction() : Super()
	, Target(nullptr)
{

}

GActorComponent::ComponentTickFunction::~ComponentTickFunction()
{

}

void GActorComponent::ComponentTickFunction::ExecuteTick(Seconds deltaTime)
{
	if (Target == nullptr)
	{
		SE_LOG(LogTicking, Error, L"Target is nullptr.");
		return;
	}

	if (Target->HasBegunPlay && Target->ComponentTickEnabled)
	{
		Target->TickComponent(deltaTime);
	}
}

GActorComponent::GActorComponent() : Super()
	, bComponentTickEnabled(true)
	, bComponentHasBegunPlay(false)
	, owner(nullptr)
{
	PrimaryComponentTick.Target = this;
}

GActorComponent::~GActorComponent()
{

}

TickFunction* GActorComponent::GetTickFunction()
{
	return &PrimaryComponentTick;
}

void GActorComponent::AddPrerequisiteObject(ITickFunctionObject* inObject)
{
	PrimaryComponentTick.AddPrerequisite(inObject);
}

void GActorComponent::RemovePrerequisiteObject(ITickFunctionObject* inObject)
{
	PrimaryComponentTick.RemovePrerequisite(inObject);
}

void GActorComponent::BeginPlay()
{
	if (owner != nullptr)
	{
		SetWorld(owner->GetWorld());
		bComponentHasBegunPlay = true;
	}
}

void GActorComponent::EndPlay()
{
	if (bComponentHasBegunPlay)
	{
		SetWorld(nullptr);
		bComponentHasBegunPlay = false;
	}
}

void GActorComponent::TickComponent(Seconds deltaTime)
{

}

AActor* GActorComponent::GetOwner() const
{
	return owner;
}

auto GActorComponent::PrimaryComponentTick_get() const -> ComponentTickFunction&
{
	return const_cast<ComponentTickFunction&>(primaryComponentTick);
}

bool GActorComponent::ComponentTickEnabled_get() const
{
	return bComponentTickEnabled;
}

void GActorComponent::ComponentTickEnabled_set(bool value)
{
	bComponentTickEnabled = true;
}

bool GActorComponent::HasBegunPlay_get() const
{
	return bComponentHasBegunPlay;
}
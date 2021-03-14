﻿// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "GameAPI.h"
#include "CoreMinimal.h"
#include "GameObject.h"

#include "TickFunction.h"

class AActor;

class GAME_API GActorComponent : public GGameObject, virtual public ITickFunctionObject
{
	friend class AActor;

	struct ComponentTickFunction : public TickFunction
	{
		using Super = TickFunction;
		using This = ComponentTickFunction;

		GActorComponent* Target;

		ComponentTickFunction();
		~ComponentTickFunction();

		void ExecuteTick(Seconds deltaTime) override;
	};

public:
	using Super = Object;
	using This = GActorComponent;

private:
	ComponentTickFunction primaryComponentTick;
	bool bComponentTickEnabled : 1;
	bool bComponentHasBegunPlay : 1;
	AActor* owner;

public:
	GActorComponent();
	~GActorComponent() override;

	virtual TickFunction* GetTickFunction() override;
	virtual void AddPrerequisiteObject(ITickFunctionObject* inObject) override;
	virtual void RemovePrerequisiteObject(ITickFunctionObject* inObject) override;

	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void TickComponent(Seconds deltaTime);

	AActor* GetOwner() const;
	template<TIsBaseOf<AActor> T>
	T* GetOwner() const;

	vs_property_get(ComponentTickFunction&, PrimaryComponentTick);
	vs_property(bool, ComponentTickEnabled);
	vs_property_get(bool, HasBegunPlay);
};

#include "ActorComponent.inl"
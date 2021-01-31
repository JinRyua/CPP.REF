﻿// Copyright 2020 Aumoa.lib. All right reserved.

#include "Levels/StartupLevel.h"

#include "Actor/MyTestActor.h"
#include "Actor/Plane.h"
#include "Pawn/MyCharacter.h"

StartupLevel::StartupLevel() : Super()
	, persistent_actor(nullptr)
	, persistent_character(nullptr)
	, plane(nullptr)
	, spectator(nullptr)
{

}

StartupLevel::~StartupLevel()
{

}

void StartupLevel::LoadLevel()
{
	persistent_actor = SpawnActorPersistent<AMyTestActor>();
	persistent_character = SpawnActorPersistent<AMyCharacter>();
	plane = SpawnActorPersistent<APlane>();
	spectator = SpawnActorPersistent<ASpectatorPawn>();
}

APawn* StartupLevel::GetPersistentActor() const
{
	return spectator;
}
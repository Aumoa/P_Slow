// Copyright 2020 Team slow. All right reserved.

#include "Manager/ReferenceManager.h"

#include "Actor/SlowPlayableCharacter.h"

void UReferenceManager::SetTypeofPlayerCharacter( TSubclassOf<ASlowPlayableCharacter> Typeof )
{
	auto Instance = GetSingletonInstance();
	Instance->TypeofPlayerCharacter = Typeof;
}

TSubclassOf<ASlowPlayableCharacter> UReferenceManager::GetTypeofPlayerCharacter()
{
	auto Instance = GetSingletonInstance();
	return Instance->TypeofPlayerCharacter;
}

UReferenceManager* UReferenceManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UReferenceManager>();
}
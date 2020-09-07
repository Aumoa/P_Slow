// Copyright 2020 Team slow. All right reserved.

#include "Manager/SpawnManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "SlowPlayableCharacterState.h"
#include "LogDefine.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Datatable/ActorReference.h"

ASlowPlayableCharacter* USpawnManager::SpawnPlayerPawn(const FTransform& Transform)
{
	auto Instance = GetSingletonInstance();
	auto World = Instance->GetWorld();

	if (World == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("USpawnManager::SpawnPlayerPawn(): GameInstance haven't world context."));
		return nullptr;
	}

	return World->SpawnActor<ASlowPlayableCharacter>(UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter")), Transform);
}

USpawnManager* USpawnManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<USpawnManager>();
}
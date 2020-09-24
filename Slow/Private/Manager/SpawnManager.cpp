// Copyright 2020 Team slow. All right reserved.

#include "Manager/SpawnManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "SlowPlayableCharacterState.h"
#include "LogDefine.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Datatable/ActorReference.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Statics/SlowNavigationSystem.h"

ASlowPlayableCharacter* USpawnManager::SpawnPlayerPawn(FTransform Transform)
{
	auto instance = GetSingletonInstance();
	auto world = instance->GetWorld();

	if (world == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("USpawnManager::SpawnPlayerPawn(): GameInstance haven't world context."));
		return nullptr;
	}

	TSubclassOf<AActor> _class = UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter"));
	FVector amendedLocation = Transform.GetLocation();

	if (FSlowNavigationSystem::FindActorStandableLocation(world, Cast<AActor>(_class->GetDefaultObject()), Transform.GetLocation(), &amendedLocation)) {
		Transform.SetLocation(amendedLocation);
	}

	return world->SpawnActor<ASlowPlayableCharacter>(UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter")), Transform);
}

USpawnManager* USpawnManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<USpawnManager>();
}
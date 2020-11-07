// Copyright 2020 Team slow. All right reserved.

#include "Manager/SpawnManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "SlowPlayableCharacterState.h"
#include "Common/SlowLogDefine.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Datatable/ActorReference.h"
#include "Statics/SlowNavigationSystem.h"

ASlowPlayableCharacter* USpawnManager::SpawnPlayerPawn(FTransform Transform)
{
	auto instance = GetSingletonInstance();
	auto world = instance->GetWorld();

	if (world == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("%s: GameInstance haven't world context."), __FUNCTIONT__);
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
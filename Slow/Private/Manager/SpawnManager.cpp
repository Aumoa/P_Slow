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

ASlowPlayableCharacter* USpawnManager::SpawnPlayerPawn(FTransform Transform, bool bCorrectionZ)
{
	auto Instance = GetSingletonInstance();
	auto World = Instance->GetWorld();

	if (World == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("USpawnManager::SpawnPlayerPawn(): GameInstance haven't world context."));
		return nullptr;
	}

	TSubclassOf<AActor> _class = UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter"));
	if (bCorrectionZ) {
		AActor* actor = _class->GetDefaultObject<AActor>();
		UCapsuleComponent* capsuleComponent = Cast<UCapsuleComponent>(actor->GetRootComponent());

		if (capsuleComponent == nullptr) {
			UE_LOG(LogSlow, Error, TEXT("USpawnManager::SpawnPlayerPawn(): bCorrectionZ is true but actor is not character(or root is not capsule component.)."));
		}
		else {
			float halfHeight = capsuleComponent->GetScaledCapsuleHalfHeight();
			FVector location = Transform.GetLocation();
			location.Z += halfHeight;
			Transform.SetLocation(location);
		}
	}

	return World->SpawnActor<ASlowPlayableCharacter>(UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter")), Transform);
}

USpawnManager* USpawnManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<USpawnManager>();
}
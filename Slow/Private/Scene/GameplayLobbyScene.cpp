// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayLobbyScene.h"

#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SpawnManager.h"
#include "Actor/SlowPlayableCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Controller/SlowPlayerController.h"

void UGameplayLobbyScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	SetNextStreamingLevel(TEXT("Map_1S"));

	USlowGameInstance* gameInstance = USlowGameInstance::GetGameInstance();

	FLatentActionInfo latentInfo;
	UGameplayStatics::LoadStreamLevel(gameInstance, TEXT("Loading"), true, true, latentInfo);
}

void UGameplayLobbyScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	FTransform initialSpawn = FTransform::Identity;
	initialSpawn.SetLocation(FVector(4200.0f, 72400.0f, 12600.0f));
	TempSpawn = USpawnManager::SpawnPlayerPawn(initialSpawn);
	InPlayerController->Possess(TempSpawn);
}

void UGameplayLobbyScene::EndPlay()
{
	Super::EndPlay();
}
// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayLobbyScene.h"

#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SpawnManager.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Controller/SlowControllerBase.h"
#include "GameFramework/GameModeBase.h"
#include "Components/CapsuleComponent.h"

void UGameplayLobbyScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	SetNextStreamingLevel(TEXT("Gameplay_Lobby"));

	USlowGameInstance* gameInstance = USlowGameInstance::GetGameInstance();

	FLatentActionInfo latentInfo;
	UGameplayStatics::LoadStreamLevel(gameInstance, TEXT("Loading"), true, true, latentInfo);
}

void UGameplayLobbyScene::BeginLevel(ASlowControllerBase* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	FTransform initialSpawn = FTransform::Identity;
	initialSpawn.SetLocation(FVector(0, 0, 10.0f));
	TempSpawn = USpawnManager::SpawnPlayerPawn(initialSpawn);
	InPlayerController->Possess(TempSpawn);
}

void UGameplayLobbyScene::EndPlay()
{
	Super::EndPlay();
}
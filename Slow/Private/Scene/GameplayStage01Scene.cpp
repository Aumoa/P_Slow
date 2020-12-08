// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayStage01Scene.h"

#include "SlowGameInstance.h"
#include "Manager/SpawnManager.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Controller/SlowPlayerController.h"
#include "Common/SlowCommonMacros.h"
#include "Common/SlowLogDefine.h"

void UGameplayStage01Scene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	StreamLoadCS = MakeUnique<FCriticalSection>();

	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();

	// 퍼시스턴트 레벨을 불러옵니다.
	UGameplayStatics::OpenLevel(WorldContext, TEXT("Map_1S_Boss_1-2"));

	
}

void UGameplayStage01Scene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	OnStreamLoaded();

	UE_LOG(LogTemp,Warning, TEXT("GameplayStage01Scene_BeginLevel()"));
}

void UGameplayStage01Scene::EndPlay()
{
	Super::EndPlay();
}

void UGameplayStage01Scene::OnStreamLoaded()
{
	GetCurrentPlayerController()->EnqueueGameThreadAction([&](UObject* InSender, UObject* InArgs)
	{
		ASlowPlayerController* const CachedPlayerController = GetCurrentPlayerController();
		UGameplayStatics::UnloadStreamLevel(CachedPlayerController, TEXT("Loading"), FLatentActionInfo(), true);

		FTransform initialSpawn = SPAWN_MANAGER.GetSpawnerTransformByType(ESpawnerType::Character);
		TempSpawn = SPAWN_MANAGER.SpawnPlayerPawn(initialSpawn);
		CachedPlayerController->Possess(TempSpawn);
	});
}
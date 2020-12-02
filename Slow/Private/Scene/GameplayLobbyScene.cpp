// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayLobbyScene.h"

#include "SlowGameInstance.h"
#include "Manager/SpawnManager.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Controller/SlowPlayerController.h"
#include "Common/SlowCommonMacros.h"
#include "Common/SlowLogDefine.h"
#include "Misc/LevelStreamingStatics.h"

UGameplayLobbyScene::UGameplayLobbyScene()
{
	bStreamLoaded_Base = false;
	bStreamLoaded_Boss1 = false;

	LevelStreamingStatics = CreateDefaultSubobject<ULevelStreamingStatics>(TEXT("LevelStreaming"));
}

void UGameplayLobbyScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();

	// 퍼시스턴트 레벨을 불러옵니다.
	UGameplayStatics::OpenLevel(WorldContext, TEXT("Map_1S"));
}

void UGameplayLobbyScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	BeginLoadLevel();

	// 비동기 로딩 작업을 진행합니다.
	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	LevelStreamingStatics->LoadSublevelGroup(WorldContext, TEXT("Base"), [&]()
		{
			OnStreamLoaded();
		}
	);
}

void UGameplayLobbyScene::EndPlay()
{
	Super::EndPlay();
}

void UGameplayLobbyScene::MigrateLevelGroup(FName LevelGroupName)
{
	BeginLoadLevel();

	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	LevelStreamingStatics->LoadSublevelGroup(WorldContext, LevelGroupName, [&]()
		{
			OnStreamLoaded();
		}
	);
}

void UGameplayLobbyScene::OnStreamLoaded()
{
	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	ASlowPlayerController* const PlayerController = Cast<ASlowPlayerController>(UGameplayStatics::GetPlayerController(WorldContext, 0));
	checkf(PlayerController != nullptr, TEXT("%s: %s에서 가져온 %s가 nullptr입니다."), __FUNCTIONT__, nameof(WorldContext), nameof(PlayerController));

	PlayerController->EnqueueGameThreadAction([&, WeakPlayerController = TWeakObjectPtr<ASlowPlayerController>(PlayerController)](UObject* InSender, UObject* InArgs)
		{
			if (!WeakPlayerController.IsValid())
			{
				UE_LOG(LogSlow, Error, TEXT("%s: %s가 올바르지 않은 값을 참조합니다. GC 또는 스레드 오류일 수 있습니다."), __FUNCTIONT__, nameof(WeakPlayerController));
				return;
			}

			ASlowPlayerController* const CachedPlayerController = WeakPlayerController.Get();

			FTransform initialSpawn = FTransform::Identity;
			initialSpawn.SetLocation(FVector(4200.0f, 72400.0f, 12600.0f));
			TempSpawn = USpawnManager::SpawnPlayerPawn(initialSpawn);
			WeakPlayerController->Possess(TempSpawn);

			EndLoadLevel();
		}
	);
}

void UGameplayLobbyScene::BeginLoadLevel()
{
	FLatentActionInfo LatentInfo;
	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	UGameplayStatics::LoadStreamLevel(WorldContext, TEXT("Loading"), true, true, LatentInfo);
}

void UGameplayLobbyScene::EndLoadLevel()
{
	FLatentActionInfo LatentInfo;
	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	UGameplayStatics::UnloadStreamLevel(WorldContext, TEXT("Loading"), FLatentActionInfo(), true);
}
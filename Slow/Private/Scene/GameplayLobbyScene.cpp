// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayLobbyScene.h"

#include "SlowGameInstance.h"
#include "Manager/SpawnManager.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Controller/SlowPlayerController.h"
#include "Common/SlowCommonMacros.h"
#include "Common/SlowLogDefine.h"
#include "Misc/LevelStreamingStatics.h"

FName UGameplayLobbyScene::LastLevelName;

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
	TOptional<float> PrevGravityScale;
	ASlowPlayableCharacter* Pawn = SPAWN_MANAGER.GetPlayerPawn();
	FName TargetLevelName = LastLevelName == NAME_None ? TEXT("Base") : LastLevelName;

	if (Pawn != nullptr)
	{
		Pawn->SetKillOffsetState(false);

		auto Movement = Cast<UCharacterMovementComponent>(Pawn->GetMovementComponent());
		if (Movement != nullptr)
		{
			SavedGravityScale = Movement->GravityScale;
			Movement->GravityScale = 0;
		}
	}

	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	LastLevelName = TargetLevelName;
	LevelStreamingStatics->LoadSublevelGroup(WorldContext, TargetLevelName, [&]()
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
	LastLevelName = LevelGroupName;
	LevelStreamingStatics->LoadSublevelGroup(WorldContext, LevelGroupName, [&]()
		{
			OnStreamLoaded();
		}
	);
}

void UGameplayLobbyScene::ReloadLevels()
{
	LevelStreamingStatics->ReloadCurrentSublevel(USlowGameInstance::GetGameInstance(), [&]()
		{
			OnStreamLoaded(true);
		}
	);
}

FName UGameplayLobbyScene::GetCurrentLevelName() const
{
	return LastLevelName;
}

void UGameplayLobbyScene::OnStreamLoaded(bool bReinitCharacter)
{
	GetCurrentPlayerController()->EnqueueGameThreadAction([&](UObject* InSender, UObject* InArgs)
		{
			ASlowPlayerController* WeakPlayerController = GetCurrentPlayerController();

			FTransform initialSpawn = SPAWN_MANAGER.GetSpawnerTransformByType(ESpawnerType::Character);
			TempSpawn = SPAWN_MANAGER.SpawnPlayerPawn(initialSpawn, bReinitCharacter);

			if (WeakPlayerController->GetPawn() == nullptr)
			{
				WeakPlayerController->Possess(TempSpawn);
			}

			auto PlayableCharacter = Cast<ASlowPlayableCharacter>(TempSpawn);
			if (PlayableCharacter != nullptr)
			{
				PlayableCharacter->RefreshKillOffset();

				if (UCharacterMovementComponent* Movement = nullptr; SavedGravityScale.IsSet() && Cast<UCharacterMovementComponent>(PlayableCharacter->GetMovementComponent()))
				{
					Movement->GravityScale = SavedGravityScale.GetValue();
					SavedGravityScale = TOptional<float>();
				}
			}

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
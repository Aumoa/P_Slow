// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayLobbyScene.h"

#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SpawnManager.h"
#include "Actor/SlowPlayableCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Controller/SlowPlayerController.h"
#include "Common/SlowCommonMacros.h"
#include "Engine/LevelStreaming.h"

UGameplayLobbyScene::UGameplayLobbyScene()
{
	bStreamLoaded_Base = false;
}

void UGameplayLobbyScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	StreamLoadCS = MakeUnique<FCriticalSection>();

	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();

	// �۽ý���Ʈ ������ �ҷ��ɴϴ�.
	UGameplayStatics::OpenLevel(WorldContext, TEXT("Map_1S"));
}

void UGameplayLobbyScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	FLatentActionInfo LatentInfo;
	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	UGameplayStatics::LoadStreamLevel(WorldContext, TEXT("Loading"), true, true, LatentInfo);

	// �񵿱� �ε� �۾��� �����մϴ�.
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = TEXT("OnStreamLoaded_Base");
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	UGameplayStatics::LoadStreamLevel(WorldContext, TEXT("Map_1S_Base"), true, false, LatentInfo);
}

void UGameplayLobbyScene::EndPlay()
{
	Super::EndPlay();
}

void UGameplayLobbyScene::OnStreamLoaded()
{
	USlowGameInstance* const WorldContext = USlowGameInstance::GetGameInstance();
	ASlowPlayerController* const PlayerController = Cast<ASlowPlayerController>(UGameplayStatics::GetPlayerController(WorldContext, 0));
	checkf(PlayerController != nullptr, TEXT("%s: %s���� ������ %s�� nullptr�Դϴ�."), __FUNCTIONT__, nameof(WorldContext), nameof(PlayerController));

	PlayerController->EnqueueGameThreadAction([&, WeakPlayerController = TWeakObjectPtr<ASlowPlayerController>(PlayerController)](UObject* InSender, UObject* InArgs)
		{
			if (!WeakPlayerController.IsValid())
			{
				UE_LOG(LogSlow, Error, TEXT("%s: %s�� �ùٸ��� ���� ���� �����մϴ�. GC �Ǵ� ������ ������ �� �ֽ��ϴ�."), __FUNCTIONT__, nameof(WeakPlayerController));
				return;
			}

			ASlowPlayerController* const CachedPlayerController = WeakPlayerController.Get();
			UGameplayStatics::UnloadStreamLevel(CachedPlayerController, TEXT("Loading"), FLatentActionInfo(), true);

			FTransform initialSpawn = FTransform::Identity;
			initialSpawn.SetLocation(FVector(4200.0f, 72400.0f, 12600.0f));
			TempSpawn = USpawnManager::SpawnPlayerPawn(initialSpawn);
			WeakPlayerController->Possess(TempSpawn);
		}
	);
}

void UGameplayLobbyScene::OnStreamLoaded_Base()
{
	ScopedLock(StreamLoadCS);

	bStreamLoaded_Base = true;

	OnStreamLoaded_CheckAndInvoke();
}

void UGameplayLobbyScene::OnStreamLoaded_CheckAndInvoke()
{
	bool bSucceeded =
		bStreamLoaded_Base;

	if (bSucceeded)
	{
		OnStreamLoaded();
	}
}
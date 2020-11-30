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

	// �۽ý���Ʈ ������ �ҷ��ɴϴ�.
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
		initialSpawn.SetLocation(FVector(28650.0f, 110880.0f, -16500.0f));
		TempSpawn = USpawnManager::SpawnPlayerPawn(initialSpawn);
		WeakPlayerController->Possess(TempSpawn);
	}
	);
}
// Copyright 2020 Team slow. All right reserved.

#include "Scene/SceneBase.h"

#include "Controller/SlowPlayerController.h"
#include "Common/SlowCommonMacros.h"
#include "Misc/LevelStreamingStatics.h"

USceneBase::USceneBase()
{
	LevelStreaming = CreateDefaultSubobject<ULevelStreamingStatics>(nameof(LevelStreaming));

	bCursorVisibleOverride = true;
	PersistentLevelName = NAME_None;
}

void USceneBase::BeginPlay(UObject* Args)
{
	UGameplayStatics::OpenLevel(this, PersistentLevelName);
}

void USceneBase::BeginLevel(ASlowPlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
	InPlayerController->bShowMouseCursor = bCursorVisibleOverride;
}

void USceneBase::EndPlay()
{

}

void USceneBase::OnActionInput(const FName& ActionName, bool bPressed)
{

}

bool USceneBase::GetCursorVisibleOverride() const
{
	return bCursorVisibleOverride;
}

ASlowPlayerController* USceneBase::GetCurrentPlayerController() const
{
	ASlowPlayerController* Ref = PlayerController.Get();
	if (Ref == nullptr)
	{
		SLOW_LOG(Error, TEXT("PlayerController that referenced on %s function is not valid on current time."), nameof_f(BeginLevel));
		return nullptr;
	}

	return Ref;
}

void USceneBase::LoadSublevelGroup(FName SublevelGroup)
{
	LevelStreaming->LoadSublevelGroup(PlayerController.Get(), SublevelGroup, [&]()
		{
			PlayerController->EnqueueGameThreadAction([&](UObject* InSender, UObject* InArgs)
				{
					UNREFERENCED_PARAMETER(InSender);
					UNREFERENCED_PARAMETER(InArgs);

					SublevelGroupLoaded.Broadcast();
				}
			);
		}
	);
}
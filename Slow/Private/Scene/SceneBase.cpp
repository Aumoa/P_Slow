// Copyright 2020 Team slow. All right reserved.

#include "Scene/SceneBase.h"

#include "Controller/SlowPlayerController.h"
#include "Common/SlowCommonMacros.h"

USceneBase::USceneBase()
{
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
		SLOW_LOG(Error, TEXT("PlayerController that referenced on BeginLevel function is not valid on current time."));
		return nullptr;
	}

	return Ref;
}
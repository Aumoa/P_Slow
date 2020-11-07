// Copyright 2020 Team slow. All right reserved.

#include "Scene/SceneBase.h"

USceneBase::USceneBase()
{
	bCursorVisibleOverride = true;
}

void USceneBase::BeginPlay(UObject* Args)
{

}

void USceneBase::BeginLevel(ASlowPlayerController* InPlayerController)
{
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

void USceneBase::SetCursorVisibleOverride(bool bVisible)
{
	bCursorVisibleOverride = bVisible;
}
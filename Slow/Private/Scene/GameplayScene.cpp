// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayScene.h"

#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"

UGameplayScene::UGameplayScene()
{
	SetCursorVisibleOverride(false);
}

void UGameplayScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);
}

void UGameplayScene::EndPlay()
{
	Super::EndPlay();
}
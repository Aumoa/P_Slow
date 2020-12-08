// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayScene.h"

#include "SlowGameInstance.h"
#include "Manager/WidgetManager.h"
#include "UI/Widget/SlowCombatUIWidget.h"

UGameplayScene::UGameplayScene()
{
	bCursorVisibleOverride = false;
}


void UGameplayScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

}

void UGameplayScene::EndPlay()
{
	Super::EndPlay();
}
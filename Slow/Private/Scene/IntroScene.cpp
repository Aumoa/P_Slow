// Copyright 2020 Team slow. All right reserved.

#include "Scene/IntroScene.h"

#include "Common/SlowLogDefine.h"
#include "Manager/SceneManager.h"
#include "Manager/WidgetManager.h"
#include "UI/Widget/IntroWidget.h"
#include "AnimInstance/SlowAnimInstance.h"
#include "Scene/GameplayLobbyScene.h"

UIntroScene::UIntroScene()
{
	PersistentLevelName = TEXT("Intro");
}

void UIntroScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);
}

void UIntroScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	USlowAnimInstance::SetManagerAccessibleState(true);

	MyMainWidget = WIDGET_MANAGER.CreateSlowWidget<UIntroWidget>(TEXT("Widget.IntroScene.IntroMain"));
}

void UIntroScene::EndPlay()
{
	if (MyMainWidget != nullptr) {
		MyMainWidget->RemoveFromParent();
		MyMainWidget = nullptr;
	}
}

void UIntroScene::OnActionInput(const FName& ActionName, bool bPressed)
{
	Super::OnActionInput(ActionName, bPressed);
}

void UIntroScene::OnIntroNextSceneInput()
{
	SCENE_MANAGER.SwitchScene(NewObject<UGameplayLobbyScene>(GetOuter()));
}
// Copyright 2020 Team slow. All right reserved.

#include "Scene/IntroScene.h"

#include "Common/SlowLogDefine.h"
#include "Manager/SceneManager.h"
#include "Manager/WidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/IntroWidget.h"
#include "AnimInstance/SlowAnimInstance.h"

void UIntroScene::BeginPlay(UObject* Args)
{
	UGameplayStatics::OpenLevel(this, TEXT("Intro"));
}

void UIntroScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	USlowAnimInstance::SetManagerAccessibleState(true);

	MyMainWidget = UWidgetManager::CreateSlowWidget<UIntroWidget>(TEXT("Widget.IntroScene.IntroMain"));
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
	USceneManager::LoadScene(TEXT("Gameplay"));
}
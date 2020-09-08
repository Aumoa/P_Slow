// Copyright 2020 Team slow. All right reserved.

#include "Scene/IntroScene.h"

#include "LogDefine.h"
#include "Manager/SceneManager.h"
#include "Manager/WidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/IntroWidget.h"

void UIntroScene::BeginPlay(UObject* Args)
{
	UE_LOG(LogSlow, Log, TEXT("UIntroScene::BeginPlay()"));

	UGameplayStatics::OpenLevel(this, TEXT("Intro"));
}

void UIntroScene::BeginLevel(ASlowControllerBase* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	MyMainWidgetLuid = UWidgetManager::AddWidgetFromReference(TEXT("MainWidget"), TEXT("Widget.IntroScene.IntroMain"), true);
	MyMainWidget = Cast<UIntroWidget>(UWidgetManager::GetWidget(MyMainWidgetLuid));
}

void UIntroScene::EndPlay()
{
	UWidgetManager::RemoveWidget(MyMainWidgetLuid);

	UE_LOG(LogSlow, Log, TEXT("UIntroScene::EndPlay()"));
}

void UIntroScene::OnActionInput(const FName& ActionName, bool bPressed)
{
	Super::OnActionInput(ActionName, bPressed);
}

void UIntroScene::OnIntroNextSceneInput()
{
	USceneManager::LoadScene(TEXT("Gameplay"));
}
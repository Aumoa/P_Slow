// Copyright 2020 Team slow. All right reserved.


#include "Scene/DemoScene.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "Manager/SceneManager.h"
#include "Manager/WidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/DemoWidget.h"

void UDemoScene::BeginPlay(UObject* Args)
{
	UE_LOG(LogSlow, Log, TEXT("UDemoScene::BeginPlay()"));

	GameInstance = USlowGameInstance::GetGameInstance();
	OpenNextScene();
}

void UDemoScene::BeginLevel(ASlowControllerBase* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	int64 luid = UWidgetManager::AddWidgetFromReference(TEXT("MainWidget"), TEXT("Widget.DemoScene.Demo"), true);
	UDemoWidget* widget = Cast<UDemoWidget>(UWidgetManager::GetWidget(luid));
	widget->DemoEnded.AddUObject(this, &UDemoScene::OnDemoEnded);

	MyWidgetLuid = luid;
}

void UDemoScene::EndPlay()
{
	UWidgetManager::RemoveWidget(MyWidgetLuid);

	UE_LOG(LogSlow, Log, TEXT("UDemoScene::EndPlay()"));
}

void UDemoScene::OnDemoEnded()
{
	USceneManager::LoadScene(TEXT("Intro"));
}

void UDemoScene::OpenNextScene()
{
	auto Config = GameInstance->GetConfig();

	if (Config->bSkipDemo) {
		OnDemoEnded();
	}
	else {
		UGameplayStatics::OpenLevel(this, TEXT("Demo"));
	}
}
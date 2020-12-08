// Copyright 2020 Team slow. All right reserved.


#include "Scene/DemoScene.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "Manager/SceneManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/ConfigManager.h"
#include "UI/Widget/DemoWidget.h"

void UDemoScene::BeginPlay(UObject* Args)
{
	GameInstance = USlowGameInstance::GetGameInstance();
	OpenNextScene();
}

void UDemoScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	MyWidget = WIDGET_MANAGER.CreateSlowWidget<UDemoWidget>(TEXT("Widget.DemoScene.Demo"));
	MyWidget->DemoEnded.AddUObject(this, &UDemoScene::OnDemoEnded);
}

void UDemoScene::EndPlay()
{
	if (MyWidget != nullptr) {
		MyWidget->RemoveFromParent();
		MyWidget = nullptr;
	}
}

void UDemoScene::OnDemoEnded()
{
	SCENE_MANAGER.LoadScene(TEXT("Intro"));
}

void UDemoScene::OpenNextScene()
{
	auto Config = CONFIG_MANAGER.GetBlueprintConfig();

	if (Config->bSkipDemo) {
		OnDemoEnded();
	}
	else {
		UGameplayStatics::OpenLevel(this, TEXT("Demo"));
	}
}
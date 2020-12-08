// Copyright 2020 Team slow. All right reserved.

#include "Scene/DemoScene.h"

#include "Manager/SceneManager.h"
#include "Manager/WidgetManager.h"
#include "UI/Widget/DemoWidget.h"
#include "Scene/IntroScene.h"
#include "Common/SlowCommonMacros.h"

UDemoScene::UDemoScene()
{
	bCursorVisibleOverride = true;
	PersistentLevelName = TEXT("Demo");
}

void UDemoScene::BeginPlay(UObject* Args)
{

}

void UDemoScene::BeginLevel(ASlowPlayerController* InPlayerController)
{
	Super::BeginLevel(InPlayerController);

	MyWidget = WIDGET_MANAGER.CreateSlowWidget<UDemoWidget>(TEXT("Widget.DemoScene.Demo"));
	MyWidget->PendingClose.AddThisUObject(OnDemoEnded);
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
	SCENE_MANAGER.SwitchScene(NewObject<UIntroScene>(GetOuter()));
}
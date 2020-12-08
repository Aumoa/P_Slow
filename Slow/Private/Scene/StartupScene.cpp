// Copyright 2020 Team slow. All right reserved.

#include "Scene/StartupScene.h"

#include "SlowConfig.h"
#include "Common/SlowConsoleVar.h"
#include "Manager/SceneManager.h"
#include "Manager/ConfigManager.h"
#include "Scene/DemoScene.h"
#include "Scene/IntroScene.h"

UStartupScene::UStartupScene()
{
	PersistentLevelName = TEXT("Startup");
}

void UStartupScene::BeginPlay( UObject* Args )
{
	Super::BeginPlay(Args);

	OpenDemoScene();
}

void UStartupScene::EndPlay()
{

}

void UStartupScene::OpenDemoScene()
{
	using namespace ConsoleVariable::Slow;

	USlowConfig* const Config = CONFIG_MANAGER.GetBlueprintConfig();

	bool bSkipDemo = SkipDemo.GetValueOnGameThread() || Config->IsSkipDemo();

	USceneBase* NextScene = nullptr;
	if (bSkipDemo)
	{
		NextScene = NewObject<UIntroScene>(GetOuter());
	}
	else
	{
		NextScene = NewObject<UDemoScene>(GetOuter());
	}

	SCENE_MANAGER.SwitchScene(NextScene);
}
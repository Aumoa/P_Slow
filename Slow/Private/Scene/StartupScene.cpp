// Copyright 2020 Team slow. All right reserved.


#include "Scene/StartupScene.h"

#include "SlowGameInstance.h"
#include "Common/SlowLogDefine.h"
#include "Common/SlowConsoleVar.h"
#include "Manager/SceneManager.h"

void UStartupScene::BeginPlay( UObject* Args )
{
	UGameplayStatics::OpenLevel( this, TEXT( "Startup" ) );

	OpenDemoScene();
}

void UStartupScene::EndPlay()
{

}

void UStartupScene::OpenDemoScene()
{
	bool bSkipDemo = ConsoleVariable::Slow::SkipDemo.GetValueOnGameThread();

	FString NextSceneName = TEXT("Demo");

	if (bSkipDemo)
	{
		NextSceneName = TEXT("Intro");
	}

	USceneManager::LoadScene(NextSceneName);
}
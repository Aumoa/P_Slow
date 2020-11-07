// Copyright 2020 Team slow. All right reserved.


#include "Scene/StartupScene.h"

#include "SlowGameInstance.h"
#include "Common/SlowLogDefine.h"
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
	USceneManager::LoadScene( TEXT( "Demo" ) );
}
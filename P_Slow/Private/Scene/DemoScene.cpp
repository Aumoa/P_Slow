// Copyright 2020. Team slow, All right reserved.


#include "Scene/DemoScene.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"
#include "SlowConfig.h"

#include "Manager/SceneManager.h"

#include "Kismet/GameplayStatics.h"

void UDemoScene::BeginPlay( UObject* Args )
{
	UE_LOG( LogSlow, Log, TEXT( "UDemoScene::BeginPlay()" ) );

	GameInstance = USlowGameInstance::GetGameInstance();
	OpenNextScene();
}

void UDemoScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UDemoScene::EndPlay()" ) );
}

void UDemoScene::OnDemoEnded()
{
	USceneManager::LoadScene( TEXT( "Intro" ) );
}

void UDemoScene::OpenNextScene()
{
	auto Config = GameInstance->Config;

	if ( Config->bSkipDemo )
	{
		OnDemoEnded();
	}
	else
	{
		UGameplayStatics::OpenLevel( this, TEXT( "Demo" ) );
	}
}
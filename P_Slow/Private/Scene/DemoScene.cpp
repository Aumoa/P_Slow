// Copyright 2020. Team slow, All right reserved.


#include "Scene/DemoScene.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"
#include "SlowConfig.h"

#include "Manager/SceneManager.h"

#include "Kismet/GameplayStatics.h"

void UDemoScene::BeginPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UDemoScene::BeginPlay()" ) );
	OpenNextScene();
}

void UDemoScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UDemoScene::EndPlay()" ) );
}

void UDemoScene::OpenNextScene()
{
	auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( this ) );
	auto Config = GameInstance->Config;

	if ( Config->bSkipDemo )
	{
		auto SceneManager = GameInstance->GetSceneManager();
		SceneManager->LoadScene( TEXT( "Intro" ) );
	}
	else
	{
		UGameplayStatics::OpenLevel( this, TEXT( "Demo" ) );
	}
}
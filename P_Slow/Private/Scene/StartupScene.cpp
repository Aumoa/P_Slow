// Copyright 2020. Team slow, All right reserved.


#include "Scene/StartupScene.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"

#include "Kismet/GameplayStatics.h"

#include "Manager/SceneManager.h"

void UStartupScene::BeginPlay( UObject* Args )
{
	UE_LOG( LogSlow, Log, TEXT( "UStartupScene::BeginPlay()" ) );

	UGameplayStatics::OpenLevel( this, TEXT( "Startup" ) );

	OpenDemoScene();
}

void UStartupScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UStartupScene::EndPlay()" ) );
}

void UStartupScene::OpenDemoScene()
{
	auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( this ) );
	auto SceneManager = GameInstance->GetSceneManager();

	SceneManager->LoadScene( TEXT( "Demo" ) );
}
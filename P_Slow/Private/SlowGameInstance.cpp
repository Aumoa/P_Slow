// Copyright 2020. Team slow, All right reserved.


#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "LogDefine.h"

#include "Manager/SceneManager.h"

void USlowGameInstance::Startup()
{
	UE_LOG( LogSlow, Log, TEXT( "USlowGameInstance::Startup()" ) );

	InitializeManagers();
}

USceneManager* USlowGameInstance::GetSceneManager()
{
	return SceneManager;
}

void USlowGameInstance::InitializeManagers()
{
	SceneManager = NewObject<USceneManager>( this );
	SceneManager->Initialize( this );
}
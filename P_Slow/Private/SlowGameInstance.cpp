// Copyright 2020. Team slow, All right reserved.


#include "SlowGameInstance.h"

#include "SlowConfig.h"
#include "LogDefine.h"

#include "Manager/SceneManager.h"
#include "Manager/SpawnManager.h"

void USlowGameInstance::Startup()
{
	UE_LOG( LogSlow, Log, TEXT( "USlowGameInstance::Startup()" ) );

	InitializeManagers();
}

USceneManager* USlowGameInstance::GetSceneManager()
{
	return SceneManager;
}

USpawnManager* USlowGameInstance::GetSpawnManager()
{
	return SpawnManager;
}

void USlowGameInstance::InitializeManagers()
{
	SceneManager = NewObject<USceneManager>( this );
	SceneManager->Initialize( this );

	SpawnManager = NewObject<USpawnManager>( this );
	SpawnManager->Initialize( this );
}
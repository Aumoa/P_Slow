// Copyright 2020. Team slow, All right reserved.


#include "SlowGameInstance.h"

#include "SlowConfig.h"
#include "LogDefine.h"

#include "Manager/SceneManager.h"
#include "Manager/SpawnManager.h"
#include "Manager/WidgetManager.h"

void USlowGameInstance::Startup()
{
	UE_LOG( LogSlow, Log, TEXT( "USlowGameInstance::Startup()" ) );

	InitializeManagers();
}

USceneManager* USlowGameInstance::GetSceneManager() const
{
	return SceneManager;
}

USpawnManager* USlowGameInstance::GetSpawnManager() const
{
	return SpawnManager;
}

UWidgetManager* USlowGameInstance::GetWidgetManager() const
{
	return WidgetManager;
}

void USlowGameInstance::InitializeManagers()
{
	SceneManager = NewObject<USceneManager>( this );
	SceneManager->Initialize( this );

	SpawnManager = NewObject<USpawnManager>( this );
	SpawnManager->Initialize( this );

	WidgetManager = NewObject<UWidgetManager>( this );
	WidgetManager->Initialize( this );
}
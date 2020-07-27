// Copyright 2020. Team slow, All right reserved.

#include "SlowGameInstance.h"

#include "Manager/SceneManager.h"
#include "Manager/SpawnManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/ConfigManager.h"
#include "Manager/ReferenceManager.h"

void USlowGameInstance::InitializeManagers()
{
	auto SceneManager = NewObject<USceneManager>( this );
	SceneManager->Initialize( this );

	auto SpawnManager = NewObject<USpawnManager>( this );
	SpawnManager->Initialize( this );

	auto WidgetManager = NewObject<UWidgetManager>( this );
	WidgetManager->Initialize( this );

	auto ConfigManager = NewObject<UConfigManager>( this );
	ConfigManager->Initialize( this );

	auto ReferenceManager = NewObject<UReferenceManager>( this );
	ReferenceManager->Initialize( this );

	Managers.Add( SceneManager );
	Managers.Add( SpawnManager );
	Managers.Add( WidgetManager );
	Managers.Add( ConfigManager );
	Managers.Add( ReferenceManager );
}
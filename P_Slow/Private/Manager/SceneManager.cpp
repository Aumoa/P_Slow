// Copyright 2020. Team slow, All right reserved.


#include "Manager/SceneManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "LogDefine.h"

void USceneManager::Initialize( USlowGameInstance* GInstance )
{
	auto Config = GInstance->Config;

	StartupScene = NewObject<USceneBase>( this, Config->StartupScene );
	DemoScene = NewObject<USceneBase>( this, Config->DemoScene );
	IntroScene = NewObject<USceneBase>( this, Config->IntroScene );
	GameplayScene = NewObject<USceneBase>( this, Config->GameplayScene );

	LoadScene( GInstance->Config->EntryPoint );
}

void USceneManager::LoadScene( const FString& SceneName, UObject* Args )
{
	bool bChanged = false;

	if ( CurrentScene )
	{
		CurrentScene->EndPlay();
	}

	CurrentScene = GetSceneByName( SceneName, bChanged );

	if ( bChanged )
	{
		CurrentScene->BeginPlay( Args );
	}
}

USceneBase* USceneManager::GetCurrentScene() const
{
	return CurrentScene;
}

USceneBase* USceneManager::GetSceneByName( const FString& SceneName, bool& bChanged ) const
{
	USceneBase* NextScene = nullptr;
	bChanged = false;

	if ( SceneName == TEXT( "Startup" ) )
	{
		NextScene = StartupScene;
	}
	else if ( SceneName == TEXT( "Demo" ) )
	{
		NextScene = DemoScene;
	}
	else if ( SceneName == TEXT( "Intro" ) )
	{
		NextScene = IntroScene;
	}
	else if ( SceneName == TEXT( "Gameplay" ) )
	{
		NextScene = GameplayScene;
	}
	else
	{
		UE_LOG( LogSlow, Error, TEXT( "Scene name: [%s] is not registered." ), *SceneName );
		return CurrentScene;;
	}

	if ( CurrentScene != NextScene )
	{
		bChanged = true;
	}

	return NextScene;
}
// Copyright 2020. Team slow, All right reserved.


#include "Manager/SceneManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"

#include "Scene/StartupScene.h"
#include "Scene/DemoScene.h"
#include "Scene/IntroScene.h"

void USceneManager::Initialize( USlowGameInstance* GInstance )
{
	StartupScene = NewObject<UStartupScene>( this );
	DemoScene = NewObject<UDemoScene>( this );
	IntroScene = NewObject<UIntroScene>( this );

	LoadScene( GInstance->Config->EntryPoint );
}

void USceneManager::LoadScene( const FString& SceneName )
{
	bool bChanged = false;

	if ( CurrentScene )
	{
		CurrentScene->EndPlay();
	}

	CurrentScene = GetSceneByName( SceneName, bChanged );

	if ( bChanged )
	{
		CurrentScene->BeginPlay();
	}
}

USceneBase* USceneManager::GetCurrentScene() const
{
	return CurrentScene;
}

USceneBase* USceneManager::GetSceneByName( const FString& SceneName, bool& bChanged ) const
{
	bChanged = false;

	if ( SceneName == TEXT( "Startup" ) )
	{
		if ( CurrentScene != StartupScene )
		{
			bChanged = true;
			return StartupScene;
		}
	}
	else if ( SceneName == TEXT( "Demo" ) )
	{
		if ( CurrentScene != DemoScene )
		{
			bChanged = true;
			return DemoScene;
		}
	}
	else if ( SceneName == TEXT( "Intro" ) )
	{
		if ( CurrentScene != IntroScene )
		{
			bChanged = true;
			return IntroScene;
		}
	}

	return CurrentScene;
}
// Copyright 2020. Team slow, All right reserved.


#include "Manager/SceneManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "LogDefine.h"

#include "Kismet/GameplayStatics.h"

void USceneManager::Initialize( USlowGameInstance* GInstance )
{
	auto Config = GInstance->Config;

	StartupScene = NewObject<USceneBase>( this, Config->StartupScene );
	DemoScene = NewObject<USceneBase>( this, Config->DemoScene );
	IntroScene = NewObject<USceneBase>( this, Config->IntroScene );
	GameplayScene = NewObject<USceneBase>( this, Config->GameplayScene );

	LoadScene( this, GInstance->Config->EntryPoint );
}

void USceneManager::LoadScene( UObject* This, const FString& SceneName, UObject* Args )
{
	auto Instance = GetSingletonInstance( This );

	bool bChanged = false;

	if ( Instance->CurrentScene )
	{
		Instance->CurrentScene->EndPlay();
	}

	Instance->CurrentScene = GetSceneByName( Instance, SceneName, bChanged );

	if ( bChanged )
	{
		Instance->CurrentScene->BeginPlay( Args );
	}
}

USceneBase* USceneManager::GetCurrentScene( UObject* This )
{
	return GetSingletonInstance( This )->CurrentScene;
}

USceneBase* USceneManager::GetSceneByName( USceneManager* Instance, const FString& SceneName, bool& bChanged )
{
	USceneBase* NextScene = nullptr;
	bChanged = false;

	if ( SceneName == TEXT( "Startup" ) )
	{
		NextScene = Instance->StartupScene;
	}
	else if ( SceneName == TEXT( "Demo" ) )
	{
		NextScene = Instance->DemoScene;
	}
	else if ( SceneName == TEXT( "Intro" ) )
	{
		NextScene = Instance->IntroScene;
	}
	else if ( SceneName == TEXT( "Gameplay" ) )
	{
		NextScene = Instance->GameplayScene;
	}
	else
	{
		UE_LOG( LogSlow, Error, TEXT( "Scene name: [%s] is not registered." ), *SceneName );
		return Instance->CurrentScene;;
	}

	if ( Instance->CurrentScene != NextScene )
	{
		bChanged = true;
	}

	return NextScene;
}

USceneManager* USceneManager::GetSingletonInstance( UObject* This )
{
	auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( This ) );
	return GameInstance->GetSceneManager();
}
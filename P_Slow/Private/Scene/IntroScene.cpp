// Copyright 2020. Team slow, All right reserved.


#include "Scene/IntroScene.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"

#include "Manager/SceneManager.h"

#include "Kismet/GameplayStatics.h"

void UIntroScene::BeginPlay( UObject* Args )
{
	UE_LOG( LogSlow, Log, TEXT( "UIntroScene::BeginPlay()" ) );

	UGameplayStatics::OpenLevel( this, TEXT( "Intro" ) );
}

void UIntroScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UIntroScene::EndPlay()" ) );
}

bool UIntroScene::OnIntroNextSceneInput( bool bPressed, const FKey& Key )
{
	auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( this ) );
	auto SceneManager = GameInstance->GetSceneManager();

	USceneManager::LoadScene( this, TEXT( "Gameplay" ) );

	return true;
}
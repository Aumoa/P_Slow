// Copyright 2020. Team slow, All right reserved.


#include "Scene/IntroScene.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"
#include "SlowInputDefine.h"

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

void UIntroScene::OnActionInput( const FName& ActionName, bool bPressed )
{
	if ( ActionName == IA_IntroNextSceneInput )
	{
		OnIntroNextSceneInput( bPressed );
	}
}

void UIntroScene::OnIntroNextSceneInput( bool bPressed )
{
	USceneManager::LoadScene( this, TEXT( "Gameplay" ) );
}
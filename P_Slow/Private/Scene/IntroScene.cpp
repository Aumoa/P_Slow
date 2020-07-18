// Copyright 2020. Team slow, All right reserved.


#include "Scene/IntroScene.h"

#include "LogDefine.h"

#include "Kismet/GameplayStatics.h"

void UIntroScene::BeginPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UIntroScene::BeginPlay()" ) );

	UGameplayStatics::OpenLevel( this, TEXT( "Intro" ) );
}

void UIntroScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UIntroScene::EndPlay()" ) );
}
// Copyright 2020. Team slow, All right reserved.


#include "Scene/IntroScene.h"

#include "LogDefine.h"

void UIntroScene::BeginPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UIntroScene::BeginPlay()" ) );
}

void UIntroScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UIntroScene::EndPlay()" ) );
}
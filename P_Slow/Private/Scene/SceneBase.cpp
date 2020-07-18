// Copyright 2020. Team slow, All right reserved.


#include "Scene/SceneBase.h"

#include "LogDefine.h"

void USceneBase::BeginPlay()
{
	UE_LOG( LogSlow, Verbose, TEXT( "USceneBase::BeginPlay() is called. The scene class must be overrided this method." ) );
}

void USceneBase::EndPlay()
{
	UE_LOG( LogSlow, Verbose, TEXT( "USceneBase::EndPlay() is called. The scene class must be overrided this method." ) );
}
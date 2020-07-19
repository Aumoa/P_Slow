// Copyright 2020. Team slow, All right reserved.


#include "Scene/SceneBase.h"

#include "LogDefine.h"

void USceneBase::BeginPlay( UObject* Args )
{
	UE_LOG( LogSlow, Error, TEXT( "USceneBase::BeginPlay() is called. The scene class must be overrided this method." ) );
}

void USceneBase::EndPlay()
{
	UE_LOG( LogSlow, Error, TEXT( "USceneBase::EndPlay() is called. The scene class must be overrided this method." ) );
}

void USceneBase::OnActionInput( const FName& ActionName, bool bPressed )
{

}
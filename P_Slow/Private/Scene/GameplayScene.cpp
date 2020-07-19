// Copyright 2020. Team slow, All right reserved.


#include "Scene/GameplayScene.h"

#include "LogDefine.h"

#include "Kismet/GameplayStatics.h"

void UGameplayScene::BeginPlay( UObject* Args )
{
	UGameplayStatics::OpenLevel( this, TEXT( "Gameplay" ) );

	NextStreamingLevel = TEXT( "EmptyLoadTest" );
}

void UGameplayScene::EndPlay()
{

}
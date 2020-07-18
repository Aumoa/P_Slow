// Copyright 2020. Team slow, All right reserved.


#include "Scene/DemoScene.h"

#include "LogDefine.h"

#include "Kismet/GameplayStatics.h"

void UDemoScene::BeginPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UDemoScene::BeginPlay()" ) );

	UGameplayStatics::OpenLevel( this, TEXT( "Demo" ) );
}

void UDemoScene::EndPlay()
{
	UE_LOG( LogSlow, Log, TEXT( "UDemoScene::EndPlay()" ) );
}

// Copyright 2020. Team slow, All right reserved.


#include "Controller/SlowPlayerController.h"

#include "SlowGameInstance.h"
#include "LogDefine.h"

#include "Manager/SceneManager.h"

#include "Components/InputComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Scene/SceneBase.h"

void ASlowPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( this ) );
}

void ASlowPlayerController::OnIntroNextSceneInput( bool bPressed, const FKey& Key )
{
	auto SceneManager = GameInstance->GetSceneManager();
	auto CurrentScene = SceneManager->GetCurrentScene();
	bool bSkipInput = CurrentScene->OnIntroNextSceneInput( bPressed, Key );
}
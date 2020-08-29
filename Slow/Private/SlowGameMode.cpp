// Copyright 2020 Team slow. All right reserved.

#include "SlowGameMode.h"

#include "Controller/SlowPlayerController.h"
#include "Actor/SlowPlayerState.h"

ASlowGameMode::ASlowGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	PlayerControllerClass = ASlowPlayerController::StaticClass();
	PlayerStateClass = ASlowPlayerState::StaticClass();
	DefaultPawnClass = nullptr;
}
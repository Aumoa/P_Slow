// Copyright 2020 Team slow. All right reserved.

#include "Manager/InputManager.h"

void UInputManager::SetPlayerController(APlayerController* playerController)
{
	auto instance = GetSingletonInstance();
	instance->PlayerController = playerController;
}

UInputManager* UInputManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UInputManager>();
}
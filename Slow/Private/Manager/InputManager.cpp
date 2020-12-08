// Copyright 2020 Team slow. All right reserved.

#include "Manager/InputManager.h"

UInputManager* UInputManager::SingletonInstance = nullptr;

void UInputManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	SingletonInstance = this;
}

void UInputManager::SetPlayerController(APlayerController* playerController)
{
	PlayerController = playerController;
}

UInputManager* UInputManager::GetInstance()
{
	return SingletonInstance;
}
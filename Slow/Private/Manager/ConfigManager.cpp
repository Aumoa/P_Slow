// Copyright 2020 Team slow. All right reserved.

#include "Manager/ConfigManager.h"

UConfigManager* UConfigManager::SingletonInstance = nullptr;

void UConfigManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	SingletonInstance = this;
}

UConfigManager* UConfigManager::GetInstance()
{
	return SingletonInstance;
}
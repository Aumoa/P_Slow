// Copyright 2020 Team slow. All right reserved.

#include "Manager/ConfigManager.h"

UConfigManager* UConfigManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UConfigManager>();
}
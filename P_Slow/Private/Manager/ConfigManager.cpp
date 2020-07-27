// Copyright 2020. Team slow, All right reserved.

#include "Manager/ConfigManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"

#include "Kismet/GameplayStatics.h"

UConfigManager* UConfigManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UConfigManager>();
}
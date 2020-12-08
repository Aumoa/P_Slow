// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "ManagerBase.h"

#include "ConfigManager.generated.h"

UCLASS()
class SLOW_API UConfigManager : public UManagerBase
{
	GENERATED_BODY()

private:
	static UConfigManager* SingletonInstance;

public:
	void Initialize(USlowGameInstance* GInstance) override;

	static UConfigManager* GetInstance();
};

#define CONFIG_MANAGER (*UConfigManager::GetInstance())
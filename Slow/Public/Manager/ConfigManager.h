// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "ManagerBase.h"

#include "ConfigManager.generated.h"

class USlowConfig;

UCLASS()
class SLOW_API UConfigManager : public UManagerBase
{
	GENERATED_BODY()

private:
	static UConfigManager* SingletonInstance;

	UPROPERTY()
	UClass* SoftClassReference;

	UPROPERTY()
	USlowConfig* Config;

public:
	UConfigManager();

	void Initialize(USlowGameInstance* GInstance) override;

	UFUNCTION(BlueprintPure)
	USlowConfig* GetBlueprintConfig() const;

	static UConfigManager* GetInstance();
};

#define CONFIG_MANAGER (*UConfigManager::GetInstance())
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "ManagerBase.h"

#include "ConfigManager.generated.h"

UCLASS()
class SLOW_API UConfigManager : public UManagerBase
{
	GENERATED_BODY()

private:
	static UConfigManager* GetSingletonInstance();
};

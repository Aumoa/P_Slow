// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "SlowGameInstance.generated.h"

class USlowConfig;
class USceneManager;

UCLASS()
class P_SLOW_API USlowGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY() USceneManager* SceneManager;

public:
	UPROPERTY( BlueprintReadWrite ) USlowConfig* Config;

public:
	UFUNCTION( BlueprintCallable ) void Startup();

	UFUNCTION( BlueprintCallable ) USceneManager* GetSceneManager();

private:
	void InitializeManagers();
};

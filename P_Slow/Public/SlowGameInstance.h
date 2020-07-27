// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "Manager/ManagerBase.h"

#include "SlowGameInstance.generated.h"

class USlowConfig;
class UManagerBase;

UCLASS()
class P_SLOW_API USlowGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	//
	// Not managed storage.
	// GameInstance will be destroyed on end of gameplay.
	static USlowGameInstance* Instance;

private:
	UPROPERTY() TArray<UManagerBase*> Managers;

public:
	UPROPERTY( BlueprintReadWrite ) USlowConfig* Config;

public:
	UFUNCTION( BlueprintCallable ) void Startup();
	UFUNCTION( BlueprintCallable ) static USlowGameInstance* GetGameInstance();

public:
	UFUNCTION( BlueprintPure ) UManagerBase* GetManager( TSubclassOf<UManagerBase> ClassType ) const;

private:
	void InitializeManagers();
};

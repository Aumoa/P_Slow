// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "Manager/ManagerBase.h"

#include "SlowGameInstance.generated.h"

class USlowConfig;
class UManagerBase;

UCLASS()
class SLOW_API USlowGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	//
	// Not managed storage.
	// GameInstance will be destroyed on end of gameplay.
	static USlowGameInstance* Instance;

private:
	UPROPERTY()
	USlowConfig* Config;
	UPROPERTY()
	TArray<UManagerBase*> Managers;

public:
	void Init() override;

	UFUNCTION(BlueprintCallable)
	USlowConfig* GetConfig() const;

	UFUNCTION(BlueprintCallable)
	static USlowGameInstance* GetGameInstance();

public:
	UFUNCTION(BlueprintPure)
	UManagerBase* GetManager(TSubclassOf<UManagerBase> ClassType) const;

private:
	void InitializeManagers();
};

#define GAME_INSTANCE (*USlowGameInstance::GetGameInstance())
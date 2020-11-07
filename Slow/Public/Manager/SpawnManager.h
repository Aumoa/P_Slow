// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "ManagerBase.h"

#include "SpawnManager.generated.h"

class ASlowPlayableCharacter;
class USlowPlayableCharacterState;
class USlowGameInstance;

UCLASS()
class SLOW_API USpawnManager : public UManagerBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SpawnManager")
	static ASlowPlayableCharacter* SpawnPlayerPawn(FTransform Transform);

private:
	static USpawnManager* GetSingletonInstance();
};

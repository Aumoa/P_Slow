// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "ManagerBase.h"

#include "ReferenceManager.generated.h"

class ASlowPlayableCharacter;

UCLASS()
class SLOW_API UReferenceManager : public UManagerBase
{
	GENERATED_BODY()

private:
	TSubclassOf<ASlowPlayableCharacter> TypeofPlayerCharacter;

public:
	UReferenceManager();

	UFUNCTION(BlueprintCallable, Category = "ReferenceManager")
	static void SetTypeofPlayerCharacter(TSubclassOf<ASlowPlayableCharacter> Typeof);

	UFUNCTION(BlueprintCallable, Category = "ReferenceManager")
	static TSubclassOf<ASlowPlayableCharacter> GetTypeofPlayerCharacter();

private:
	static UReferenceManager* GetSingletonInstance();
};
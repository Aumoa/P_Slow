// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "SpawnManager.generated.h"

class ASlowPlayableCharacter;
class USlowPlayableCharacterState;

UCLASS()
class P_SLOW_API USpawnManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize( UObject* This );

	UFUNCTION( BlueprintCallable, Category = "SpawnManager" ) static ASlowPlayableCharacter* SpawnPlayerPawn( UObject* This, const FTransform& Transform );
};

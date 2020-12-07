// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "ManagerBase.h"

#include "Components/SpawnerComponent.h"

#include "SpawnManager.generated.h"

class ASlowPlayableCharacter;
class USlowPlayableCharacterState;
class USlowGameInstance;

UCLASS()
class SLOW_API USpawnManager : public UManagerBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASlowPlayableCharacter* CorePlayerChar;

	TMap<ESpawnerType, USpawnerComponent*> Spawners;
	TMap<FString, USpawnerComponent*> CustomSpawners;
	
public:
	USpawnManager();

	UFUNCTION(BlueprintCallable, Category = "SpawnManager")
	ASlowPlayableCharacter* SpawnPlayerPawn(FTransform Transform, bool bForceSpawn = false);

	UFUNCTION(BlueprintPure, Category = "SpawnManager")
	ASlowPlayableCharacter* GetPlayerPawn() const;

	UFUNCTION(BlueprintCallable, Category = "SpawnManager")
	void AddSpawner(USpawnerComponent* InSpawner);

	UFUNCTION(BlueprintCallable, Category = "SpawnManager")
	void RemoveSpawner(USpawnerComponent* InSpawner);

	UFUNCTION(BlueprintPure, Category = "SpawnManager")
	FTransform GetSpawnerTransformByType(ESpawnerType InType) const;

	UFUNCTION(BlueprintPure, Category = "SpawnManager")
	FTransform GetSpawnerTransformByCustomKey(const FString& InCustomKey) const;

private:
	FTransform GetSpawnerTransform(USpawnerComponent* Spawner) const;

	static USpawnManager* GetSingletonInstance();
};

#ifdef GAME_INSTANCE
#define SPAWN_MANAGER (*((USpawnManager*)GAME_INSTANCE.GetManager(USpawnManager::StaticClass())))
#endif
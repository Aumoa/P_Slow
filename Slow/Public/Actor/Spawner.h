// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "Spawner.generated.h"

class USpawnerComponent;

UCLASS()
class SLOW_API ASpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USpawnerComponent* SpawnerComponent;

public:
	ASpawner();
};
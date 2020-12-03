// Copyright 2020 Team slow. All right reserved.

#include "Actor/Spawner.h"

#include "Components/SpawnerComponent.h"

ASpawner::ASpawner()
{
	Root = CreateDefaultSubobject<USceneComponent>(nameof(Root));
	RootComponent = Root;

	SpawnerComponent = CreateDefaultSubobject<USpawnerComponent>(nameof(SpawnerComponent));
	AddOwnedComponent(SpawnerComponent);
}
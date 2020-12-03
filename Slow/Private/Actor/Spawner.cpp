// Copyright 2020 Team slow. All right reserved.

#include "Actor/Spawner.h"

#include "Components/SpawnerComponent.h"

ASpawner::ASpawner()
{
	Root = CreateDefaultSubobject<USceneComponent>(nameof(Root));
	RootComponent = Root;

	Root->SetMobility(EComponentMobility::Static);

	SpawnerComponent = CreateDefaultSubobject<USpawnerComponent>(nameof(SpawnerComponent));
	AddOwnedComponent(SpawnerComponent);
}
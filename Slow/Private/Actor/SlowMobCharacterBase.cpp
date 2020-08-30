// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowMobCharacterBase.h"

#include "Components/StatComponent.h"

ASlowMobCharacterBase::ASlowMobCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	AddOwnedComponent(StatComponent);
}

void ASlowMobCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowMobCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
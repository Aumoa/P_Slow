// Copyright 2020 Team slow. All right reserved.

#include "Components/StatComponent.h"

#include "LogDefine.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bBeginMaxCurrent = true;
}

void UStatComponent::BeginPlay()
{
	if (bBeginMaxCurrent) {
		CurrentHealth = MaxHealth;
	}
}

void UStatComponent::ApplyDamage(const FRelativeDamage& Damage)
{

}
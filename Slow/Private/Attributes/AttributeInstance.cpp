// Copyright 2020 Team slow. All right reserved.

#include "Attributes/AttributeInstance.h"

#include "Structures/RelativeDamage.h"
#include "Structures/BaseAttributeConfig.h"

void UAttributeInstance::BeginPlay(const FBaseAttributeConfig& config)
{
	configRef = &config;
	health = config.StartHealth;
}

void UAttributeInstance::ApplyDamage(const FRelativeDamage& relativeDamage)
{
	health += relativeDamage.RelativeHealth;
}

bool UAttributeInstance::IsPendingKill() const
{
	return health <= 0;
}
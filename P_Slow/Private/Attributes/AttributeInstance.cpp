// Copyright 2020 Team slow. All right reserved.

#include "Attributes/AttributeInstance.h"

FAttributeInstance::FAttributeInstance()
{

}

void FAttributeInstance::ApplyDamage(const FRelativeDamage& relativeDamage)
{
	Health += relativeDamage.RelativeHealth;
}

bool FAttributeInstance::IsPendingKill() const
{
	return Health <= 0;
}
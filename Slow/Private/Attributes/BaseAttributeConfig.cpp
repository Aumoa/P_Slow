// Copyright 2020 Team slow. All right reserved.

#include "Attributes/BaseAttributeConfig.h"

FBaseAttributeConfig::FBaseAttributeConfig()
{
	MinHealth = 0;
	MaxHealth = 100;
	StartHealth = MaxHealth;
	MinStamina = 0;
	MaxStamina = 100;
	StartStamina = 100;
	DefaultDamage = 0;
	FaintPercent = 0.16f;
	FriendlyName = TEXT("");

}
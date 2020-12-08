// Copyright 2020 Team slow. All right reserved.

#include "SlowConfig.h"

#include "Scene/StartupScene.h"
#include "Scene/IntroScene.h"

#include "Ability/HatchetWeapon.h"
#include "Ability/SwordWeapon.h"
#include "Ability/HammerWeapon.h"

USlowConfig::USlowConfig( const FObjectInitializer& Initializer ) : Super( Initializer )
{
	bSkipDemo = false;

	HatchetWeapon = UHatchetWeapon::StaticClass();
	SwordWeapon = USwordWeapon::StaticClass();
	HammerWeapon = UHammerWeapon::StaticClass();
}

bool USlowConfig::IsSkipDemo() const
{
	return bSkipDemo;
}

TSubclassOf<UWeaponBase> USlowConfig::GetHatchetWeaponClass() const
{
	return HatchetWeapon;
}

TSubclassOf<UWeaponBase> USlowConfig::GetSwordWeaponClass() const
{
	return SwordWeapon;
}

TSubclassOf<UWeaponBase> USlowConfig::GetHammerWeaponClass() const
{
	return HammerWeapon;
}
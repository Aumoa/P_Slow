// Copyright 2020. Team slow, All right reserved.


#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"

void UHammerWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
}

void UHammerWeapon::EndWeapon()
{

}

bool UHammerWeapon::SwapConditionInternal()
{

	return true;
}
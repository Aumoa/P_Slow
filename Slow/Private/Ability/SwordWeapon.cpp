// Copyright 2020. Team slow, All right reserved.


#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"

void USwordWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
}

void USwordWeapon::EndWeapon()
{
	
}

bool USwordWeapon::SwapConditionInternal()
{

	return true;
}
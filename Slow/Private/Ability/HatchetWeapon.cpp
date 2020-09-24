// Copyright 2020. Team slow, All right reserved.


#include "Ability/HatchetWeapon.h"
#include "Manager/WeaponManager.h"

void UHatchetWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
}

void UHatchetWeapon::EndWeapon()
{

}

bool UHatchetWeapon::SwapConditionInternal()
{

	return true;
}
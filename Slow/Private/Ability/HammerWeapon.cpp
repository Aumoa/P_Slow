// Copyright 2020. Team slow, All right reserved.


#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

void UHammerWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));
}

void UHammerWeapon::EndWeapon()
{

}

bool UHammerWeapon::SwapConditionInternal()
{

	return true;
}
// Copyright 2020. Team slow, All right reserved.


#include "Ability/HatchetWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

void UHatchetWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hatchet"));
}

void UHatchetWeapon::EndWeapon()
{

}

bool UHatchetWeapon::SwapConditionInternal()
{

	return true;
}
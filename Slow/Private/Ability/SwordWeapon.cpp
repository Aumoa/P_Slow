// Copyright 2020. Team slow, All right reserved.


#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

void USwordWeapon::BeginWeapon()
{
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Sword"));
}

void USwordWeapon::EndWeapon()
{
	
}

bool USwordWeapon::SwapConditionInternal()
{

	return true;
}
// Copyright 2020. Team slow, All right reserved.


#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

void USwordWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Sword"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Sword Damage : %d"), WeaponReferenceTable->Damage));
}

void USwordWeapon::EndWeapon()
{
	
}

bool USwordWeapon::SwapConditionInternal()
{

	return true;
}
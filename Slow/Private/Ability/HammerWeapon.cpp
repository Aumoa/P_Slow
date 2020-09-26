// Copyright 2020. Team slow, All right reserved.


#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

void UHammerWeapon::BeginWeapon()
{
	UWeaponManager::SetSwapAnimState(true);
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Hammer Damage : %d"), WeaponReferenceTable->Damage));
}

void UHammerWeapon::EndWeapon()
{

}

bool UHammerWeapon::SwapConditionInternal()
{

	return true;
}
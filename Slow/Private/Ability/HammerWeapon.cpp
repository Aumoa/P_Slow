// Copyright 2020. Team slow, All right reserved.


#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

void UHammerWeapon::BeginWeapon()
{
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));
	//WeaponMesh = ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_Weapon(TEXT("Game/Slow/Meshes/Weapon/Hammer/SM_WeaponHammer.SM_WeaponHammer"));
}

void UHammerWeapon::EndWeapon()
{

}

bool UHammerWeapon::SwapConditionInternal()
{

	return true;
}
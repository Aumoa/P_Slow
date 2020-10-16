// Copyright 2020. Team slow, All right reserved.


#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

USwordWeapon::USwordWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Sword/SM_WeaponSword.SM_WeaponSword'"));
	StaticMesh_Weapon = SM_W.Object;
}

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

UStaticMesh* USwordWeapon::GetWeaponMesh()
{
	return StaticMesh_Weapon;
}
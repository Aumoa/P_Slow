// Copyright 2020. Team slow, All right reserved.


#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

UHammerWeapon::UHammerWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Hammer/SM_WeaponHammer.SM_WeaponHammer'"));
	StaticMesh_Weapon = SM_W.Object;

	SocketName = TEXT("HammerSocket");
}

void UHammerWeapon::BeginWeapon()
{
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));
	
}

void UHammerWeapon::EndWeapon()
{

}

bool UHammerWeapon::SwapConditionInternal()
{

	return true;
}

UStaticMesh* UHammerWeapon::GetWeaponMesh()
{
	return StaticMesh_Weapon;
}

FName UHammerWeapon::GetSocketName()
{
	return SocketName;
}

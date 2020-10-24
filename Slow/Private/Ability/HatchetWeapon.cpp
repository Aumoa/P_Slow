// Copyright 2020. Team slow, All right reserved.


#include "Ability/HatchetWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

UHatchetWeapon::UHatchetWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Hatchet/SM_WeaponHatchet.SM_WeaponHatchet'"));
	StaticMesh_Weapon = SM_W.Object;
	
	SocketName = TEXT("HatchetSocket");
}

void UHatchetWeapon::BeginWeapon()
{
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hatchet"));
}

void UHatchetWeapon::EndWeapon()
{

}

bool UHatchetWeapon::SwapConditionInternal()
{

	return true;
}

UStaticMesh* UHatchetWeapon::GetWeaponMesh()
{
	return StaticMesh_Weapon;
}

FName UHatchetWeapon::GetSocketName()
{
	return SocketName;
}

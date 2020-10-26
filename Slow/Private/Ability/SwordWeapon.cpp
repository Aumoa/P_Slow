// Copyright 2020. Team slow, All right reserved.


#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"

USwordWeapon::USwordWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Sword/SM_WeaponSword.SM_WeaponSword'"));
	StaticMesh_Weapon = SM_W.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Attack_Sword.MTG_PC_Attack_Sword'"));
	AttackMontage = Attack_MTG.Object;
}

void USwordWeapon::BeginWeapon()
{
	SocketName = TEXT("SwordSocket");

	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Sword"));
	ComboList.Empty();

	ComboList.Emplace(TEXT("Sword_Combo1"));
	ComboList.Emplace(TEXT("Sword_Combo2"));
	ComboList.Emplace(TEXT("Sword_Combo3"));
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

FName USwordWeapon::GetSocketName()
{
	return SocketName;
}

int USwordWeapon::GetMaxComboCount()
{
	return ComboList.Num();
}

UAnimMontage* USwordWeapon::GetAttackMontage()
{
	if (AttackMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HammerWeapon, AttackMontage is Nullptr."));
	}

	return AttackMontage;
}

TArray<FName> USwordWeapon::GetComboList()
{
	return ComboList;
}
// Copyright 2020. Team slow, All right reserved.


#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Animation/AnimMontage.h"

UHammerWeapon::UHammerWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Hammer/SM_WeaponHammer.SM_WeaponHammer'"));
	StaticMesh_Weapon = SM_W.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Attack_ham.MTG_PC_Attack_ham'"));
	AttackMontage = Attack_MTG.Object;

}

void UHammerWeapon::BeginWeapon()
{
	SocketName = TEXT("HammerSocket");

	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));

	ComboList.Empty();
	ComboList.Emplace(TEXT("Hammer_Combo1"));
	ComboList.Emplace(TEXT("Hammer_Combo2"));
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

int UHammerWeapon::GetMaxComboCount()
{
	return ComboList.Num();
}

UAnimMontage* UHammerWeapon::GetAttackMontage()
{
	if (AttackMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HammerWeapon, AttackMontage is Nullptr."));
	}

	return AttackMontage;
}

TArray<FName> UHammerWeapon::GetComboList()
{
	return ComboList;
}
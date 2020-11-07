// Copyright 2020. Team slow, All right reserved.


#include "Ability/HatchetWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Components/CapsuleComponent.h"

UHatchetWeapon::UHatchetWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Hatchet/SM_WeaponHatchet.SM_WeaponHatchet'"));
	StaticMesh_Weapon = SM_W.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Attack_Hat.MTG_PC_Attack_Hat'"));
	AttackMontage = Attack_MTG.Object;

	Collision_Weapon = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision_Weapon"));
	Collision_Weapon->SetCapsuleHalfHeight(60);
	Collision_Weapon->SetCapsuleRadius(20);
	Collision_Weapon->SetRelativeLocationAndRotation(FVector(11, 0, -7),FRotator(0,-10,0));
}

void UHatchetWeapon::BeginWeapon()
{
	SocketName = TEXT("HatchetSocket");

	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hatchet"));

	ComboList.Empty();
	ComboList.Emplace(TEXT("Hatchet_Combo1"));
	ComboList.Emplace(TEXT("Hatchet_Combo2"));
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

int UHatchetWeapon::GetMaxComboCount()
{
	return ComboList.Num();
}

UAnimMontage* UHatchetWeapon::GetAttackMontage()
{
	if (AttackMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HammerWeapon, AttackMontage is Nullptr."));
	}

	return AttackMontage;
}

TArray<FName> UHatchetWeapon::GetComboList()
{
	return ComboList;
}

UCapsuleComponent* UHatchetWeapon::GetCapsuleComponent()
{
	return Collision_Weapon;
}

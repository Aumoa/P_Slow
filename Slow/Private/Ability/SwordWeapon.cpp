// Copyright 2020. Team slow, All right reserved.

#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Requirement/CostRequirement.h"
#include "Requirement/CooldownRequirement.h"

USwordWeapon::USwordWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Sword/SM_WeaponSword.SM_WeaponSword'"));
	StaticMesh_Weapon = SM_W.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Attack_Sword.MTG_PC_Attack_Sword'"));
	AttackMontage = Attack_MTG.Object;

	Collision_Weapon = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision_Weapon"));
	Collision_Weapon->SetCapsuleHalfHeight(70);
	Collision_Weapon->SetCapsuleRadius(6.6f);
	Collision_Weapon->SetRelativeLocation(FVector(0, -2, -15));
}

void USwordWeapon::BeginWeapon()
{
	SocketName = TEXT("SwordSocket");

	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Sword"));
	
	TSharedPtr<FCostRequirement> Cost_Weapon = MakeShared<FCostRequirement>();
	Cost_Weapon->SetupUsageCount(WeaponReferenceTable->MaxUsageCount);
	TSharedPtr<FCooldownRequirement> Cooldown_Weapon = MakeShared<FCooldownRequirement>();
	Cooldown_Weapon->SetupCooldown(WeaponReferenceTable->SwapCoolDown);

	Requirements_Weapon.Add(Cost_Weapon);
	Requirements_Weapon.Add(Cooldown_Weapon);

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

TArray<TSharedPtr<FRequirementBase>> USwordWeapon::GetAllRequirements() const
{
	return Requirements_Weapon;
}

TSubclassOf<UBehavior> USwordWeapon::GetEffect() const
{
	return UBehavior::StaticClass();
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

UCapsuleComponent* USwordWeapon::GetCapsuleComponent()
{
	return Collision_Weapon;
}

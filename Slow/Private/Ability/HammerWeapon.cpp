// Copyright 2020. Team slow, All right reserved.

#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Requirement/CostRequirement.h"
#include "Requirement/CooldownRequirement.h"
#include "Components/Behavior.h"

UHammerWeapon::UHammerWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Hammer/SM_WeaponHammer.SM_WeaponHammer'"));
	StaticMesh_Weapon = SM_W.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Attack_ham.MTG_PC_Attack_ham'"));
	AttackMontage = Attack_MTG.Object;

	Collision_Weapon = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision_Weapon"));
	Collision_Weapon->SetCapsuleHalfHeight(70);
	Collision_Weapon->SetCapsuleRadius(35);
	Collision_Weapon->SetRelativeRotation(FRotator(90.0f,0.0f,0.0f));
}

void UHammerWeapon::BeginWeapon()
{
	SocketName = TEXT("HammerSocket");
	
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));

	TSharedPtr<FCostRequirement> Cost_Weapon = MakeShared<FCostRequirement>();
	Cost_Weapon->SetupUsageCount(WeaponReferenceTable->MaxUsageCount);
	TSharedPtr<FCooldownRequirement> Cooldown_Weapon = MakeShared<FCooldownRequirement>();
	Cooldown_Weapon->SetupCooldown(WeaponReferenceTable->SwapCoolDown);

	Requirements_Weapon.Add(Cost_Weapon);
	Requirements_Weapon.Add(Cooldown_Weapon);

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

TArray<TSharedPtr<FRequirementBase>> UHammerWeapon::GetAllRequirements() const
{
	return Requirements_Weapon;
}

TSubclassOf<UBehavior> UHammerWeapon::GetEffect() const
{
	return UBehavior::StaticClass();
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

UCapsuleComponent* UHammerWeapon::GetCapsuleComponent()
{
	return Collision_Weapon;
}

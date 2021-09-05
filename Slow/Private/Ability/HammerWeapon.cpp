// Copyright 2020. Team slow, All right reserved.

#include "Ability/HammerWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Requirement/CostRequirement.h"
#include "Requirement/CooldownRequirement.h"
#include "Components/Behavior.h"
#include "Effect/StatModifyLinearEffect.h"
#include "Actor/SlowStatBasedCharacter.h"
#include "Ability/AttackAbility.h"

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

void UHammerWeapon::AddAttackImmediateEffect()
{
	if (!AttackAbility)
	{
		return;
	}

	AttackAbility->FAttackImmediateEffect.AddUFunction(this, FName("ConsumeWeaponCost"));
}

void UHammerWeapon::AddAttackHitEffect()
{
	if (!AttackAbility)
	{
		return;
	}

	//AttackAbility->FAttackHitEffect.Add()
}

void UHammerWeapon::BeginWeapon(AActor *Owner)
{
	MyOwner = Owner;
	SocketName = TEXT("HammerSocket");
	
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Hammer"));

	TSharedPtr<FCostRequirement> Cost_Weapon = MakeShared<FCostRequirement>();;
	Cost_Weapon->SetupUsageCount(WeaponReferenceTable->MaxUsageCount);

	TSharedPtr<FCooldownRequirement> Cooldown_Weapon = MakeShared<FCooldownRequirement>();
	Cooldown_Weapon->SetupCooldown(WeaponReferenceTable->SwapCoolDown);

	FAttrInstance MondifyValue = {};
	MondifyValue.AttackDamage = WeaponReferenceTable->Damage;

	FStatModifyLinearEffect* DamageEffect = new FStatModifyLinearEffect(MyOwner, MondifyValue);

	WeaponEffectList.Add(DamageEffect);
	
	Requirements_Weapon.Add(Cost_Weapon);
	Requirements_Weapon.Add(Cooldown_Weapon);

	ComboList.Empty();
	ComboList.Emplace(TEXT("Hammer_Combo1"));
	ComboList.Emplace(TEXT("Hammer_Combo2"));

	ASlowStatBasedCharacter* SlowCharacter = Cast<ASlowStatBasedCharacter>(Owner);
	if (SlowCharacter)
	{
		AttackAbility = SlowCharacter->GetFAttackAbility();
	}

	AddAttackImmediateEffect();
	AddAttackHitEffect();
}

void UHammerWeapon::EndWeapon()
{
	AttackAbility->FAttackImmediateEffect.Clear();
	AttackAbility->FAttackHitEffect.Clear();
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

FWeaponReferenceTableRow* UHammerWeapon::GetWeaponDataTableRow()
{
	return WeaponReferenceTable;
}

void UHammerWeapon::ConsumeWeaponCost()
{
	for (TSharedPtr<FRequirementBase> Requirement : Requirements_Weapon)
	{
		TSharedPtr<FCostRequirement> CostRequirement = StaticCastSharedPtr<FCostRequirement>(Requirement);
		if (CostRequirement != nullptr)
		{
			CostRequirement->Consume(1);
		}
	}
}

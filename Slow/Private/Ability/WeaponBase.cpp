// Copyright 2020. Team slow, All right reserved.

#include "Ability/WeaponBase.h"

TArray<TSharedPtr<FRequirementBase>> UWeaponBase::GetAllRequirements() const
{
	return { };
}

TSubclassOf<UBehavior> UWeaponBase::GetEffect() const
{
	return nullptr;
}

TArray<FActorEffect*> UWeaponBase::GetEffectList()
{
	return WeaponEffectList;
}

void UWeaponBase::AddAttackImmediateEffect()
{
}

void UWeaponBase::AddAttackHitEffect()
{
}


void UWeaponBase::BeginWeapon(AActor *Owner)
{
	
}

void UWeaponBase::EndWeapon()
{
	
}

bool UWeaponBase::SwapConditionInternal()
{
	return true;
}

UStaticMesh* UWeaponBase::GetWeaponMesh()
{
	return nullptr;
}

FName UWeaponBase::GetSocketName()
{
	return FName();
}

int UWeaponBase::GetMaxComboCount()
{
	return 0;
}

UAnimMontage* UWeaponBase::GetAttackMontage()
{
	return nullptr;
}

TArray<FName> UWeaponBase::GetComboList()
{
	return TArray<FName>();
}

UCapsuleComponent* UWeaponBase::GetCapsuleComponent()
{
	return nullptr;
}

FWeaponReferenceTableRow* UWeaponBase::GetWeaponDataTableRow()
{
	return nullptr;
}





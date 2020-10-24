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

void UWeaponBase::BeginWeapon()
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





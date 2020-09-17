// Copyright 2020. Team slow, All right reserved.


#include "Manager/WeaponManager.h"
#include "SlowConfig.h"
#include "SlowGameInstance.h"

void UWeaponManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	auto Config = GInstance->GetConfig();

	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->HatchetWeapon));
	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->SwordWeapon));
	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->HammerWeapon));

}

void UWeaponManager::NextWeapon()
{
	//ÇÞÃÂ -> ½º¿öµå -> ÇÜ¸Ó ¼øÈ¯
}

void UWeaponManager::ThrowingWeapon()
{

}

UWeaponManager* UWeaponManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UWeaponManager>();
}
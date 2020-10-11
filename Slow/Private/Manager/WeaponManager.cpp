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
	CurrentWeapon = WeaponArray[0];
	SwapAnimState = false;
	
}

UWeaponManager* UWeaponManager::GetInstance()
{
	auto Instance = GetSingletonInstance();

	if(Instance)
		return Instance;

	return nullptr;
}

void UWeaponManager::NextWeapon()
{
	auto Instance = GetSingletonInstance();

	if (Instance->SwapCondition(Instance->CurrentWeapon))
	{
		Instance->CurrentWeapon->EndWeapon();

		Instance->CurrentWeapon = Instance->WeaponArray[(Instance->WeaponArray.Find(Instance->CurrentWeapon) + 1)
														%Instance->WeaponArray.Num()];

		Instance->CurrentWeapon->BeginWeapon();
	}
	
}

void UWeaponManager::ThrowingWeapon()
{
	auto Instance = GetSingletonInstance();


}

UWeaponManager* UWeaponManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UWeaponManager>();
}

bool UWeaponManager::SwapCondition(UWeaponBase *Weapon)
{
	if (Weapon->SwapConditionInternal())
	{
		//무기 외부 고려 사항 (예시: 기절, 침묵 상태 등 무기를 교체할 수 없는 상황 정의)

		return true;
	}

	else
	{
		return false;
	}		
}

int UWeaponManager::GetWeaponNum()
{
	auto Instance = GetSingletonInstance();

	return Instance->CurrentWeapon == nullptr ? -1 : Instance->WeaponArray.Find(Instance->CurrentWeapon);
}

void UWeaponManager::SetSwapAnimState(const bool Animstate)
{
	auto Instance = GetSingletonInstance();
	
	Instance->SwapAnimState = Animstate;
}

bool UWeaponManager::GetSwapAnimState()
{
	auto Instance = GetSingletonInstance();

	if (Instance->SwapAnimState)
	{
		Instance->SetSwapAnimState(false);

		return true;
	}

	else
		return false;
	
}

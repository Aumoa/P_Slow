// Copyright 2020. Team slow, All right reserved.


#include "Manager/WeaponManager.h"
#include "SlowConfig.h"
#include "SlowGameInstance.h"
#include "Manager/ManagerBase.h"

/*void UWeaponManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	auto Config = GInstance->GetConfig();

	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->HatchetWeapon));
	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->SwordWeapon));
	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->HammerWeapon));
	CurrentWeapon = WeaponArray[0];
	SwapAnimState = false;
	
}*/


void UWeaponManager::Init()
{
	USlowGameInstance* GInstance = USlowGameInstance::GetGameInstance();
	auto Config = GInstance->GetConfig();

	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->HatchetWeapon));
	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->SwordWeapon));
	WeaponArray.Emplace(NewObject<UWeaponBase>(this, Config->HammerWeapon));
	CurrentWeapon = WeaponArray[0];
	
}

UWeaponManager::UWeaponManager()
{
	SwapAnimState = false;
}

/*UWeaponManager* UWeaponManager::GetInstance()
{
	auto Instance = GetSingletonInstance();

	if(Instance)
		return Instance;

	return nullptr;
}*/

void UWeaponManager::NextWeapon()
{
	if (SwapCondition(CurrentWeapon))
	{
		CurrentWeapon->EndWeapon();

		CurrentWeapon = WeaponArray[(WeaponArray.Find(CurrentWeapon) + 1)
														%WeaponArray.Num()];

		CurrentWeapon->BeginWeapon();
		SetSwapAnimState(true);
	}
	
}

void UWeaponManager::ThrowingWeapon()
{

}

/*UWeaponManager* UWeaponManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UWeaponManager>();
}*/

bool UWeaponManager::SwapCondition(UWeaponBase *Weapon)
{
	if (Weapon != nullptr)
	{
		if (Weapon->SwapConditionInternal())
		{
			//���� �ܺ� ��� ���� (����: ����, ħ�� ���� �� ���⸦ ��ü�� �� ���� ��Ȳ ����)

			return true;
		}

		else
		{
			return false;
		}
	}

	return false;
}

int UWeaponManager::GetWeaponNum()
{
	return CurrentWeapon == nullptr ? -1 : WeaponArray.Find(CurrentWeapon);
}

void UWeaponManager::SetSwapAnimState(const bool Animstate)
{
	SwapAnimState = Animstate;
}

bool UWeaponManager::GetSwapAnimState()
{

	if (SwapAnimState)
	{
		SetSwapAnimState(false);

		return true;
	}

	else
		return false;
	
}

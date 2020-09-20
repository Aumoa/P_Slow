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
	
}

void UWeaponManager::NextWeapon()
{
	auto Instance = GetSingletonInstance();

	if (Instance->SwapCondition(Instance->CurrentWeapon))
	{
		Instance->CurrentWeapon = Instance->WeaponArray[(Instance->WeaponArray.Find(Instance->CurrentWeapon) + 1)
														%Instance->WeaponArray.Num()];

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Swap Weapon : %d"), Instance->WeaponArray.Find(Instance->CurrentWeapon)));
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
		//���� �ܺ� ��� ���� (����: ����, ħ�� ���� �� ���⸦ ��ü�� �� ���� ��Ȳ ����)

		return true;
	}

	else
	{
		return false;
	}		
}
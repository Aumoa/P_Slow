// Copyright 2020. Team slow, All right reserved.

#include "Manager/WeaponManager.h"

#include "SlowConfig.h"
#include "Manager/ConfigManager.h"
#include "Ability/WeaponBase.h"
#include "Ability/HatchetWeapon.h"
#include "Ability/HammerWeapon.h"
#include "Ability/SwordWeapon.h"

void UWeaponManager::Init(AActor *Owner)
{
	MyOwner = Owner;

	auto Config = CONFIG_MANAGER.GetBlueprintConfig();

	WeaponArray.Empty();

	HammerWeapon = NewObject<UWeaponBase>(this, Config->GetHammerWeaponClass());
	SwordWeapon = NewObject<UWeaponBase>(this, Config->GetSwordWeaponClass());
	HatchetWeapon = NewObject<UWeaponBase>(this, Config->GetHatchetWeaponClass());

	WeaponArray.Emplace(HammerWeapon);
	WeaponArray.Emplace(SwordWeapon);
	WeaponArray.Emplace(HatchetWeapon);
	CurrentWeapon = nullptr;

	IsBattle = false;
}

UWeaponManager::UWeaponManager()
{
	SwapAnimState = false;
}



void UWeaponManager::NextWeapon()
{
	if (CurrentWeapon == nullptr)
	{
		CurrentWeapon = WeaponArray[0];

		CurrentWeapon->BeginWeapon(MyOwner);
		SetSwapAnimState(true);

		IsBattle = true;

		return;
	}
	

	if (WeaponArray.Find(CurrentWeapon) != INDEX_NONE)
	{
		if (SwapCondition(CurrentWeapon))
		{
			CurrentWeapon->EndWeapon();

			CurrentWeapon = WeaponArray[(WeaponArray.Find(CurrentWeapon)+1)%WeaponArray.Num()];
				
			CurrentWeapon->BeginWeapon(MyOwner);
			SetSwapAnimState(true);

			IsBattle = true;
		}
				
	}
	
	
}

void UWeaponManager::ThrowingWeapon()
{

}


bool UWeaponManager::SwapCondition(UWeaponBase *Weapon)
{
	if (Weapon != nullptr)
	{
		if (Weapon->SwapConditionInternal())
		{
			//무기 외부 고려 사항 (예시: 기절, 침묵 상태 등 무기를 교체할 수 없는 상황 정의)

			return true;
		}
	}

	return false;
}

UWeaponBase* UWeaponManager::GetCurrentWeapon()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon;
	}

	return nullptr;
}

int UWeaponManager::GetWeaponNum() const
{
	if (CurrentWeapon != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("Fix after Num :: %d"), WeaponArray.Find(CurrentWeapon));
		//UE_LOG(LogTemp, Log, TEXT("Weapon[0]Name :: %s"), *WeaponArray[0]->GetName());
		
		return WeaponArray.Find(CurrentWeapon);
	}
	return -1;
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

bool UWeaponManager::GetIsBattle()
{
	return IsBattle;
}

void UWeaponManager::SetPeaceMode()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->EndWeapon();
		CurrentWeapon = nullptr;
		IsBattle = false;
	}
}

UStaticMesh* UWeaponManager::GetWeaponMeshObject()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetWeaponMesh();
	}

	return nullptr;
}

FName UWeaponManager::GetSocketName()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetSocketName();
	}

	return TEXT("None_Socket");
}

int UWeaponManager::GetMaxComboCount()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetMaxComboCount();
	}

	return -1;
}

UAnimMontage* UWeaponManager::GetAttackMontage()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetAttackMontage();
	}
	
	return nullptr;
}

TArray<FName> UWeaponManager::GetComboList()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetComboList();
	}

	return TArray<FName>();
}

UCapsuleComponent* UWeaponManager::GetCapsuleComponent()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetCapsuleComponent();
	}

	return nullptr;
}

FWeaponReferenceTableRow* UWeaponManager::GetWeaponDataTable()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetWeaponDataTableRow();
	}

	return nullptr;
}

// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "ManagerBase.h"

#include "WeaponManager.generated.h"

class USlowGameInstance;
class UWeaponBase;

UCLASS()
class SLOW_API UWeaponManager : public UManagerBase
{
	GENERATED_BODY()


private:
	UPROPERTY()
	UWeaponBase *CurrentWeapon;

	UPROPERTY()
	TArray<UWeaponBase*> WeaponArray;
	

public:
	void Initialize(USlowGameInstance* GInstance) override;

	static void NextWeapon(); 
	//////////////////////////////////////////////////////////////////////////
	// <Client Request>														//
	//______________________________________________________________________//
	// 내구도가 없으면 무기 사용 불가능										//
	// 무기 교체 [햇쳇 -> 스워드 -> 도끼 순환]									//
	// 교체 쿨타임 4초														//
	//////////////////////////////////////////////////////////////////////////

	static void ThrowingWeapon(); 


private:
	static UWeaponManager* GetSingletonInstance();
	bool SwapCondition(UWeaponBase* Weapon);
};

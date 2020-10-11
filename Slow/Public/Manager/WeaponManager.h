// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "ManagerBase.h"

#include "WeaponManager.generated.h"

class USlowGameInstance;
class UWeaponBase;
class UManagerBase;

UCLASS()
class SLOW_API UWeaponManager : public UObject
{
	GENERATED_BODY()


private:
	UPROPERTY()
	UWeaponBase *CurrentWeapon;

	UPROPERTY()
	TArray<UWeaponBase*> WeaponArray;

	UPROPERTY()
	bool SwapAnimState;
	

public:
	//void Initialize(USlowGameInstance* GInstance) override;

	UWeaponManager();
	void Init();

	//UWeaponManager* GetInstance();
	void NextWeapon(); 
	//////////////////////////////////////////////////////////////////////////
	// <Client Request>														//
	//______________________________________________________________________//
	// 내구도가 없으면 무기 사용 불가능										//
	// 무기 교체 [햇쳇 -> 스워드 -> 도끼 순환]									//
	// 교체 쿨타임 4초														//
	//////////////////////////////////////////////////////////////////////////

	void ThrowingWeapon();

	int GetWeaponNum();
	void SetSwapAnimState(const bool Animstate);
	bool GetSwapAnimState();


private:
	//static UWeaponManager* GetSingletonInstance();
	bool SwapCondition(UWeaponBase* Weapon);
	
};

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
	// �������� ������ ���� ��� �Ұ���										//
	// ���� ��ü [���� -> ������ -> ���� ��ȯ]									//
	// ��ü ��Ÿ�� 4��														//
	//////////////////////////////////////////////////////////////////////////

	void ThrowingWeapon();

	int GetWeaponNum();
	void SetSwapAnimState(const bool Animstate);
	bool GetSwapAnimState();


private:
	//static UWeaponManager* GetSingletonInstance();
	bool SwapCondition(UWeaponBase* Weapon);
	
};

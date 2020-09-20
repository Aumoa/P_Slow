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
	// �������� ������ ���� ��� �Ұ���										//
	// ���� ��ü [���� -> ������ -> ���� ��ȯ]									//
	// ��ü ��Ÿ�� 4��														//
	//////////////////////////////////////////////////////////////////////////

	static void ThrowingWeapon(); 


private:
	static UWeaponManager* GetSingletonInstance();
	bool SwapCondition(UWeaponBase* Weapon);
};

// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "ManagerBase.h"

#include "WeaponManager.generated.h"

class USlowGameInstance;
class UWeaponBase;
class UManagerBase;
class UStaticMesh;

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
	UWeaponBase *HammerWeapon;
	UPROPERTY()
	UWeaponBase *SwordWeapon;
	UPROPERTY()
	UWeaponBase *HatchetWeapon;


	int CurrentWeaponNum;
	bool SwapAnimState;
	

public:
	//void Initialize(USlowGameInstance* GInstance) override;

	UWeaponManager();
	void Init();

	void NextWeapon(); 
	//////////////////////////////////////////////////////////////////////////
	// <Client Request>														//
	//______________________________________________________________________//
	// 내구도가 없으면 무기 사용 불가능										//
	// 무기 교체 [햇쳇 -> 스워드 -> 도끼 순환]									//
	// 교체 쿨타임 4초														//
	//////////////////////////////////////////////////////////////////////////

	void ThrowingWeapon();

	int GetWeaponNum() const;
	void SetSwapAnimState(const bool Animstate);
	bool GetSwapAnimState();
	UStaticMesh* GetWeaponMeshObject();
	FName GetSocketName();


private:
	bool SwapCondition(UWeaponBase* Weapon);
	
};

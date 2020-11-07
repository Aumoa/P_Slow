// Copyright 2020. Team slow, All right reserved.

#pragma once


#include "Ability/WeaponBase.h"

#include "SwordWeapon.generated.h"

struct FWeaponReferenceTableRow;
class UAnimMontage;
class UCapsuleComponent;

UCLASS()
class SLOW_API USwordWeapon : public UWeaponBase
{
	GENERATED_BODY()

private:
	USwordWeapon();

private:
	FWeaponReferenceTableRow *WeaponReferenceTable;

	UPROPERTY()
	UStaticMesh* StaticMesh_Weapon;
	
	UPROPERTY()
	UCapsuleComponent* Collision_Weapon;

	UPROPERTY()
	FName SocketName;

	UPROPERTY()
	class UAnimMontage* AttackMontage;

	UPROPERTY()
	TArray<FName> ComboList;

public:
	void BeginWeapon() override;

	void EndWeapon() override;

	bool SwapConditionInternal() override;

	UStaticMesh* GetWeaponMesh() override;

	FName GetSocketName() override;

	int GetMaxComboCount() override;
	UAnimMontage* GetAttackMontage() override;
	TArray<FName> GetComboList() override;
	UCapsuleComponent* GetCapsuleComponent() override;
};

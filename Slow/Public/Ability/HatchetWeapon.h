// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability/WeaponBase.h"

#include "HatchetWeapon.generated.h"

struct FWeaponReferenceTableRow;
class UAnimMontage;

UCLASS()
class SLOW_API UHatchetWeapon : public UWeaponBase
{
	GENERATED_BODY()

private:
	UHatchetWeapon();

private:
	FWeaponReferenceTableRow *WeaponReferenceTable;

	UPROPERTY()
	UStaticMesh* StaticMesh_Weapon;
	UPROPERTY()
	FName SocketName;

	UPROPERTY()
	UAnimMontage* AttackMontage;

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
};

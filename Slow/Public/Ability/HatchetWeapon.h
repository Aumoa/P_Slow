// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability/WeaponBase.h"

#include "HatchetWeapon.generated.h"

struct FWeaponReferenceTableRow;

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

public:
	void BeginWeapon() override;

	void EndWeapon() override;

	bool SwapConditionInternal() override;

	UStaticMesh* GetWeaponMesh();
};

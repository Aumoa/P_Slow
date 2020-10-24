// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability/WeaponBase.h"

#include "HammerWeapon.generated.h"

struct FWeaponReferenceTableRow;

UCLASS()
class SLOW_API UHammerWeapon : public UWeaponBase
{
	GENERATED_BODY()

private:
	UHammerWeapon();


	FWeaponReferenceTableRow *WeaponReferenceTable;

	UPROPERTY()
	UStaticMesh *StaticMesh_Weapon;
	UPROPERTY()
	FName SocketName;

public:
	void BeginWeapon() override;

	void EndWeapon() override;

	bool SwapConditionInternal() override;

	UStaticMesh* GetWeaponMesh() override;

	FName GetSocketName() override;
};

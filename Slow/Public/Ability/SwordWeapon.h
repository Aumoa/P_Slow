// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability/WeaponBase.h"

#include "SwordWeapon.generated.h"

struct FWeaponReferenceTableRow;

UCLASS()
class SLOW_API USwordWeapon : public UWeaponBase
{
	GENERATED_BODY()

private:
	FWeaponReferenceTableRow *WeaponReferenceTable;

public:
	void BeginWeapon() override;

	void EndWeapon() override;

	bool SwapConditionInternal() override;
};

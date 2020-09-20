// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability/WeaponBase.h"

#include "HammerWeapon.generated.h"

UCLASS()
class SLOW_API UHammerWeapon : public UWeaponBase
{
	GENERATED_BODY()

public:
	void BeginWeapon() override;

	void EndWeapon() override;

	bool SwapConditionInternal() override;

};

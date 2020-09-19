// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"

class ILocationTargetAbility : virtual public FAbilityBase
{
public:
	ILocationTargetAbility();

	virtual void SetTarget(const FVector& InLocation) = 0;
};
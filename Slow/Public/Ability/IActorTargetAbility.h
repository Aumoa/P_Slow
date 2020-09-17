// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"

class AActor;

class IActorTargetAbility : virtual public FAbilityBase
{
public:
	IActorTargetAbility();

	virtual void SetTarget(AActor* InActor) = 0;
};
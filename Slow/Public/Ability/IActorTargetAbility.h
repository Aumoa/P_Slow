// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "AbilityBase.h"

class ASlowCharacter;

class IActorTargetAbility : virtual public FAbilityBase
{
public:
	IActorTargetAbility();

	virtual void SetTarget(ASlowCharacter* InActor) = 0;

	virtual TWeakObjectPtr<ASlowCharacter> GetTarget();
};
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

class FAbilityBase;

class FAbilitySlot
{
	TWeakPtr<FAbilityBase> Ability;

public:
	FAbilitySlot();
	
	void SetAbility(FAbilityBase* InAbility);
	TWeakPtr<FAbilityBase> GetAbility() const;
};
// Copyright 2020 Team slow. All right reserved.

#include "Ability/AbilitySlot.h"

#include "Ability/AbilityBase.h"

FAbilitySlot::FAbilitySlot()
{

}

void FAbilitySlot::SetAbility(FAbilityBase* InAbility)
{
	Ability = InAbility->AsShared();
}

TWeakPtr<FAbilityBase> FAbilitySlot::GetAbility() const
{
	if (Ability.IsValid()) {
		return Ability;
	}
	else {
		return nullptr;
	}
}
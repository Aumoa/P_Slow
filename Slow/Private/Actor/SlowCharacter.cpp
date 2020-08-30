// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowCharacter.h"

ASlowCharacter::ASlowCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CombatTag.bCanTarget = true;
}

const FCombatTag& ASlowCharacter::GetCombatTag() const
{
	return CombatTag;
}
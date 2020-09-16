// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowCharacter.h"

ASlowCharacter::ASlowCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CombatTag.bCanTarget = true;
}

void ASlowCharacter::SetCombatTag(const FCombatTag& InCombatTag)
{
	CombatTag = InCombatTag;
}

FCombatTag ASlowCharacter::GetCombatTag() const
{
	return CombatTag;
}
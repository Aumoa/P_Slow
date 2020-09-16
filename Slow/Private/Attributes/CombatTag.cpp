// Copyright 2020 Team slow. All right reserved.

#include "Attributes/CombatTag.h"

FCombatTag::FCombatTag()
{
	bCanTarget = false;
}

bool FCombatTag::CheckFlagsOn(const FCombatTag& InTag) const
{
	bool bCheck = true;

	if (bCheck && InTag.bCanTarget) bCheck = bCanTarget;

	return bCheck;
}

bool FCombatTag::CheckFlagsOff(const FCombatTag& InTag) const
{
	bool bCheck = true;

	if (bCheck && InTag.bCanTarget) bCheck = !bCanTarget;

	return bCheck;
}
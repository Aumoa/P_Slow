// Copyright 2020 Team slow. All right reserved.

#include "Requirement/CombatRequirement.h"

#include "Actor/SlowCharacter.h"

FCombatRequirement::FCombatRequirement()
{

}

bool FCombatRequirement::Query(ASlowCharacter* InCharacter) const
{
	if (InCharacter == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("FCombatRequirement::Query(): InCharacter is null."));
		return false;
	}

	FCombatTag inCharacterTag = InCharacter->GetCombatTag();

	bool bOnRequire = inCharacterTag.CheckFlagsOn(FlagsOnRequire);
	bool bOffRequire = inCharacterTag.CheckFlagsOff(FlagsOffRequire);

	return GetResult(bOnRequire || bOffRequire);
}

void FCombatRequirement::SetRequireFlagsOn(const FCombatTag& InCombatTag)
{
	FlagsOnRequire = InCombatTag;
}

FCombatTag FCombatRequirement::GetRequireFlagsOn() const
{
	return FlagsOnRequire;
}

void FCombatRequirement::SetRequireFlagsOff(const FCombatTag& InCombatTag)
{
	FlagsOffRequire = InCombatTag;
}

FCombatTag FCombatRequirement::GetRequireFlagsOff() const
{
	return FlagsOffRequire;
}
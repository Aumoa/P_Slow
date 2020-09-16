// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "RequirementBase.h"

#include "Attributes/CombatTag.h"

class ASlowCharacter;

class FCombatRequirement : public FRequirementBase
{
	FCombatTag FlagsOnRequire;
	FCombatTag FlagsOffRequire;

public:
	FCombatRequirement();

	virtual bool Query(ASlowCharacter* InCharacter) const;

	void SetRequireFlagsOn(const FCombatTag& InCombatTag);
	FCombatTag GetRequireFlagsOn() const;
	void SetRequireFlagsOff(const FCombatTag& InCombatTag);
	FCombatTag GetRequireFlagsOff() const;
};
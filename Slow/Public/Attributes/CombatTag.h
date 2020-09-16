// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "CombatTag.generated.h"

USTRUCT(BlueprintType)
struct FCombatTag
{
	GENERATED_BODY()

public:
	FCombatTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 bCanTarget : 1;

	bool CheckFlagsOn(const FCombatTag& InTag) const;
	bool CheckFlagsOff(const FCombatTag& InTag) const;
};
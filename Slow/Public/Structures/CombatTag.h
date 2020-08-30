// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "CombatTag.generated.h"

USTRUCT(BlueprintType)
struct FCombatTag
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 bCanTarget : 1;
};
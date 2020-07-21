// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Damage.generated.h"

USTRUCT( Atomic, BlueprintType )
struct P_SLOW_API FDamage
{
	GENERATED_BODY()

public:
	FDamage();

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FixedAmount" ) int64 FixedHealth;
};

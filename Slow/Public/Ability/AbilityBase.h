// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AbilityBase.generated.h"

class ASlowStatBasedCharacter;

UCLASS()
class SLOW_API UAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	UAbilityBase();

	virtual void ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer);
	virtual void CancelIndirect();
};
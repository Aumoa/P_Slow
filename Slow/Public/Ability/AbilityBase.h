// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

class ASlowStatBasedCharacter;

class FAbilityBase : public TSharedFromThis<FAbilityBase>
{
public:
	FAbilityBase();
	virtual ~FAbilityBase();

	virtual void ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer);
	virtual void CancelIndirect();
};
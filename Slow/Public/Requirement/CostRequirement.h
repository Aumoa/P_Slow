// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "RequirementBase.h"

#include "CostRequirement.generated.h"

UCLASS()
class SLOW_API UCostRequirement : public URequirementBase
{
	GENERATED_BODY()

public:
	UCostRequirement();

	int32 ConsumeCount;
};
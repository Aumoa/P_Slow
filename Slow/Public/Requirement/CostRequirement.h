// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "RequirementBase.h"

class FCostRequirement : public FRequirementBase
{
public:
	FCostRequirement();

	int32 ConsumeCount;
};
// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "RequirementBase.h"

class FCostRequirement : public FRequirementBase
{
public:
	FCostRequirement();

	int32 ConsumeCount;
};
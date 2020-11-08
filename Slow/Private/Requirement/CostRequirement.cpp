// Copyright 2020 Team slow. All right reserved.

#include "Requirement/CostRequirement.h"

FCostRequirement::FCostRequirement()
{
	BaseUsageCount = 0;
	ActiveUsageCount = 0;
}

void FCostRequirement::SetupUsageCount(float InUsageCount)
{
	if (InUsageCount <= 0)
	{
		InUsageCount = 0;
	}

	BaseUsageCount = InUsageCount;

	BaseUsageCount = InUsageCount;
	ResetUsageCount();
}

bool FCostRequirement::Consume(float InUsedCount)
{
	bool bValid;

	ActiveUsageCount -= InUsedCount;
	if (ActiveUsageCount <= 0)
	{
		ActiveUsageCount = 0;
		bValid = true;
	}
	else
	{
		bValid = false;
	}

	return GetResult(bValid);
}

bool FCostRequirement::IsValid() const
{
	bool bValid = ActiveUsageCount <= 0;

	return GetResult(bValid);
}

void FCostRequirement::ResetUsageCount()
{
	ActiveUsageCount = BaseUsageCount;
}

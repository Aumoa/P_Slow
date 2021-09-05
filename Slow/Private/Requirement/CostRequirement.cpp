// Copyright 2020 Team slow. All right reserved.

#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"
#include "Requirement/CostRequirement.h"

FCostRequirement::FCostRequirement()
{
	BaseUsageCount = 0;
	ActiveUsageCount = 0;
	CastChecker = true;
}

bool FCostRequirement::SelfCheck() const
{
	bool bValid = false;

	if (ActiveUsageCount > 0)
	{
		bValid = true;
		UE_LOG(LogSlow, Error, TEXT("%s: bValid = true"), __FUNCTIONT__);
	}

	return GetResult(bValid);
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
	if (!CastChecker)
	{
		return GetResult(false);
	}

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
	UE_LOG(LogSlow, Error, TEXT("%s: 남은 무기 횟수: %d 중에 %d"), __FUNCTIONT__, ActiveUsageCount, BaseUsageCount);
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

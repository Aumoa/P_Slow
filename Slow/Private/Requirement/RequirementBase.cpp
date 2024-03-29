// Copyright 2020 Team slow. All right reserved.

#include "Requirement/RequirementBase.h"

FRequirementBase::FRequirementBase()
{
	bInvertCheck = false;
}

bool FRequirementBase::SelfCheck() const
{
	return GetResult(true);
}

void FRequirementBase::SetInvertCheck(bool bFlag)
{
	bInvertCheck = bFlag;
}

bool FRequirementBase::IsInvertCheck() const
{
	return bInvertCheck;
}

bool FRequirementBase::GetResult(bool bQueryRequireResult) const
{
	return bInvertCheck != bQueryRequireResult;
}
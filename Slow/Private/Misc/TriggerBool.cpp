// Copyright 2020 Team slow. All right reserved.

#include "Misc/TriggerBool.h"

FTriggerBool::FTriggerBool(bool bInValue) : bValue(bInValue)
{

}

void FTriggerBool::SetValue(bool bInValue)
{
	bValue = bInValue;
}

bool FTriggerBool::GetValue() const
{
	return bValue;
}

bool FTriggerBool::GetValueAndReset()
{
	bool bLeft = bValue;
	bValue = false;
	return bLeft;
}
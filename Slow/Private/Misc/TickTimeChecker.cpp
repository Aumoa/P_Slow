// Copyright 2020 Team slow. All right reserved.

#include "Misc/TickTimeChecker.h"

FTickTimeChecker::FTickTimeChecker()
{
	bReached = false;

	Timer = 0;
	DesiredTime = 0;
}

void FTickTimeChecker::Tick(float InDeltaSeconds)
{
	if (!IsReached())
	{
		Timer += InDeltaSeconds;
	}
}

void FTickTimeChecker::Reset(float InDesiredTime)
{
	Timer = 0;
	DesiredTime = InDesiredTime;
}

bool FTickTimeChecker::IsReached() const
{
	return Timer >= DesiredTime;
}
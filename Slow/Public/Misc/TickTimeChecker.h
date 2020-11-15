// Copyright 2020 Team slow. All right reserved.

#pragma once

class SLOW_API FTickTimeChecker : public FNoncopyable
{
	uint8 bReached : 1;
	
	float Timer;
	float DesiredTime;

public:
	FTickTimeChecker();

	void Tick(float InDeltaSeconds);
	void Reset(float InDesiredTime);
	bool IsReached() const;
};
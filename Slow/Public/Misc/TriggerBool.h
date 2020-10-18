// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

class FTriggerBool
{
	bool bValue;

public:
	FTriggerBool(bool bInValue = false);

	void SetValue(bool bInValue);
	bool GetValue() const;
	bool GetValueAndReset();
};
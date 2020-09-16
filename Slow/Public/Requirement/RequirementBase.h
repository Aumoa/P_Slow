// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

class FRequirementBase
{
	uint8 bInvertCheck : 1;

public:
	FRequirementBase();

	void SetInvertCheck(bool bFlag);
	bool IsInvertCheck() const;

protected:
	bool GetResult(bool bQueryRequireResult) const;
};
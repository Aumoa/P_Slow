// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Structures/RelativeDamage.h"

class FAttributeInstance
{
	int64 Health;

public:
	FAttributeInstance();

	void ApplyDamage(const FRelativeDamage& relativeDamage);

	bool IsPendingKill() const;
};
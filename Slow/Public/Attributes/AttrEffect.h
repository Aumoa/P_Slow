// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

class UAttributeInstance;

class FAttrEffect
{
public:
	FAttrEffect();

	virtual bool ApplyEffect(UAttributeInstance* InAttrInstance) = 0;
};
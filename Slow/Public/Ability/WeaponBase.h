// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WeaponBase.generated.h"

UCLASS(Blueprintable)
class SLOW_API UWeaponBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginWeapon();
	virtual void EndWeapon();
	virtual bool SwapConditionInternal();
	//가상함수 구현
};

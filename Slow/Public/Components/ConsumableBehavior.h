// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "Behavior.h"

#include "ConsumableBehavior.generated.h"

UCLASS()
class SLOW_API UConsumableBehavior : public UBehavior
{
	GENERATED_BODY()

private:
	int32 ConsumableCount;

public:
	UConsumableBehavior();

	virtual int32 GetStackCount() const;
	virtual bool Consume(int32 InConsumeCount = 1);
	virtual int32 ConsumeAll();

protected:
	virtual void ModifyStackCount(int32 InStackCount = 1, bool bSet = false);
};
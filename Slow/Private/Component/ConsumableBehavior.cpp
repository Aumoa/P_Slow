// Copyright 2020 Team slow. All right reserved.

#include "Component/ConsumableBehavior.h"

UConsumableBehavior::UConsumableBehavior()
{
	ConsumableCount = 0;
}

int32 UConsumableBehavior::GetStackCount() const
{
	return ConsumableCount;
}

bool UConsumableBehavior::Consume(int32 InConsumeCount)
{
	if (ConsumableCount >= InConsumeCount) {
		ConsumableCount -= InConsumeCount;
		return true;
	}
	
	return false;
}

int32 UConsumableBehavior::ConsumeAll()
{
	int32 left = ConsumableCount;
	ConsumableCount = 0;
	return left;
}

void UConsumableBehavior::ModifyStackCount(int32 InStackCount, bool bSet)
{
	if (bSet) {
		ConsumableCount = InStackCount;
	}
	else {
		ConsumableCount += InStackCount;
	}
}
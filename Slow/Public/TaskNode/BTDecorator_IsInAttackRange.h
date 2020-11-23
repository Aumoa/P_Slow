// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "BTDecorator_IsInAttackRange.generated.h"

UCLASS()
class SLOW_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
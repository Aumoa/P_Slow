// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "BTDecorator_IsGeneralCondition.generated.h"

UCLASS()
class SLOW_API UBTDecorator_IsGeneralCondition : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsGeneralCondition();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

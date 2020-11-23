// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "BTTask_TurnToTarget.generated.h"


UCLASS()
class SLOW_API UBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TurnToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
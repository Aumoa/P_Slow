// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "BTTask_FourWayAttack.generated.h"

UCLASS()
class SLOW_API UBTTask_FourWayAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FourWayAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsAttacking = false;
	float DeltaAttack = 0.0f;
};
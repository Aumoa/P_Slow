// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "BTTask_FindPatrolPos.generated.h"

UCLASS()
class SLOW_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
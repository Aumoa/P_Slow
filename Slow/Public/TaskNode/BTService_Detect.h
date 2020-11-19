// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "BTService_Detect.generated.h"

UCLASS()
class SLOW_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
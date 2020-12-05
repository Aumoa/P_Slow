// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTDecorator_IsGeneralCondition.h"
#include "Actor/SlowStatBasedCharacter.h"

UBTDecorator_IsGeneralCondition::UBTDecorator_IsGeneralCondition()
{
	NodeName = TEXT("IsGeneralCondition");
}

bool UBTDecorator_IsGeneralCondition::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ASlowStatBasedCharacter *ControllingPawn = Cast<ASlowStatBasedCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	bResult = ControllingPawn->GetBehaviorCoolDown() <= 0.0f;

	return bResult;
}

// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTDecorator_IsInAttackRange.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}
	
	auto Target = Cast<ASlowStatBasedCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASlowMobController::TargetKey));
	if (Target == nullptr)
	{
		return false;
	}

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 500.0f);

	return bResult;
}

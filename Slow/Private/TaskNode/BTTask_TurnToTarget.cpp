// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTTask_TurnToTarget.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<ASlowStatBasedCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<ASlowStatBasedCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASlowMobController::TargetKey));
	if (Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - Character ->GetActorLocation();
	LookVector.Z = 0.0f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//Character->SetActorRotation(FMath::RInterpTo(Character->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(),1.0f));
	Character->SetActorRotation(TargetRot);
	UE_LOG(LogTemp,Warning, TEXT("UBTTask_TurnToTarget::ExecuteTask() : TargetRot (%f,%f,%f)"),TargetRot.Roll, TargetRot.Pitch, TargetRot.Yaw);

	return EBTNodeResult::Succeeded;
}

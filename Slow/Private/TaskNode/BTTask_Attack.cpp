// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTTask_Attack.h"
#include "Actor/SlowStatBasedCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ASlowStatBasedCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//UE_LOG(LogTemp, Warning, TEXT("BTTask_Attack :: character : %s"), *character->GetName());
	character->Attack();
	IsAttacking = true;

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);
	
	
	if (DeltaAttack >= 2.3f)
	{
		DeltaAttack = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	else
	{
		DeltaAttack+=DeltaSeconds;
		
	}
}

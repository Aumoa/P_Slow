// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTTask_Attack.h"
#include "Actor/SlowMobCharacterBase.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ASlowMobCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//UE_LOG(LogTemp, Warning, TEXT("BTTask_Attack :: character : %s"), *character->GetName());

	int32 RandNum = FMath::RandRange(0, 2);

	character->PlayMontage(character->GetAttackMontage(RandNum));
	UE_LOG(LogTemp, Warning, TEXT("BTTask_Attack :: Rand Num : %d"), RandNum);
	IsAttacking = true;

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);
	
	
	if (DeltaAttack >= 2.8f)
	{
		DeltaAttack = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	else
	{
		DeltaAttack+=DeltaSeconds;
		
	}
}

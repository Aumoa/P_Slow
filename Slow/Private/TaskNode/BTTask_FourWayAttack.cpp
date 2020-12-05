// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTTask_FourWayAttack.h"
#include "Actor/SlowStatBasedCharacter.h"
#include "Actor/SlowMobCharacterBase.h"

UBTTask_FourWayAttack::UBTTask_FourWayAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FourWayAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ASlowMobCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//UE_LOG(LogTemp, Warning, TEXT("BTTask_Attack :: character : %s"), *character->GetName());

	character->PlayMontage(character->GetAttackMontage(0));

	IsAttacking = true;

	return EBTNodeResult::InProgress;
}

void UBTTask_FourWayAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	if (DeltaAttack >= 2.8f)
	{
		DeltaAttack = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	else
	{
		DeltaAttack += DeltaSeconds;

	}
}

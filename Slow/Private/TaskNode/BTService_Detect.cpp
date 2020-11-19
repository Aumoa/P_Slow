// Copyright 2020 Team slow. All right reserved.

#include "TaskNode/BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

	APawn *ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return;
	}

	UWorld *World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 1400.0f;

	if (World == nullptr)
	{
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
		);

	if (bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASlowMobController::TargetKey, nullptr);

		for (auto OverlapResult : OverlapResults)
		{
			ASlowStatBasedCharacter* character = Cast<ASlowStatBasedCharacter>(OverlapResult.GetActor());


			if (character && character->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASlowMobController::TargetKey,	character);

				UE_LOG(LogTemp,Warning,TEXT("BTService_Detect :: Player Found : %s"),*character->GetName());
				return;
			}
		}

		
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 1.0f);
}

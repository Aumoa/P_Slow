// Copyright 2020 Aumoa.lib. All right reserved.

#include "Controller/SlowMobController.h"

const FName ASlowMobController::HomePosKey(TEXT("HomePos"));
const FName ASlowMobController::PatrolPoskey(TEXT("PatrolPos"));
const FName ASlowMobController::TargetKey(TEXT("Target"));

ASlowMobController::ASlowMobController()
{
	PrimaryActorTick.bCanEverTick = true;

	bValidPossess = false;

	RepeatInterval = 3.0f;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(
						TEXT("BlackboardData'/Game/Slow/AI/Boss1/BB_Boss1.BB_Boss1'"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(
						TEXT("BehaviorTree'/Game/Slow/AI/Boss1/BT_Boss1.BT_Boss1'"));

	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ASlowMobController::OnPossess(APawn* InTarget)
{
	Super::OnPossess(InTarget);

	MobCharacter = Cast<ASlowMobCharacterBase>(InTarget);
	bValidPossess = MobCharacter.IsValid();

	if (MobCharacter == nullptr)
	{
		return;
	}

	if (bValidPossess == false)
	{
		return;
	}

	if (!UseBlackboard(BBAsset, Blackboard))
	{
		return;
	}

	Blackboard->SetValueAsVector(HomePosKey, InTarget->GetActorLocation());

	if (!RunBehaviorTree(BTAsset))
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle,this,
					&ASlowMobController::OnRepeatTimer, RepeatInterval, true);
}

void ASlowMobController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();

	if (CurrentPawn == nullptr)
	{
		return;
	}

	UNavigationSystemV1 *NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem == nullptr)
	{
		return;
	}

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);

	}
}


void ASlowMobController::OnUnPossess()
{
	Super::OnUnPossess();

	MobCharacter = nullptr;
	bValidPossess = false;
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

bool ASlowMobController::IsValidPossess() const
{
	return bValidPossess;
}
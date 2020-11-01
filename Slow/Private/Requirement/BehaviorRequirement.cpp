// Copyright 2020 Team slow. All right reserved.

#include "Requirement/BehaviorRequirement.h"

#include "Common/SlowLogDefine.h"
#include "Components/Behavior.h"
#include "Actor/SlowCharacter.h"

FBehaviorRequirement::FBehaviorRequirement()
{
	bCheckIsActivated = true;
}

bool FBehaviorRequirement::SelfCheck() const
{
	return true;
}

bool FBehaviorRequirement::ActorTargetCheck(AActor* InActor) const
{
	auto InCharacter = Cast<ASlowCharacter>(InActor);
	if (InCharacter == nullptr)
	{
		return GetResult(false);
	}
	else
	{
		return Query(InCharacter);
	}
}

bool FBehaviorRequirement::Query(ASlowCharacter* InCharacter) const
{
	if (InCharacter == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("%s: %s parameter is null."), __FUNCTIONT__, nameof(InCharacter));
		return false;
	}

	if (TypeofBehavior == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("%s: %s is null."), __FUNCTIONT__, nameof(TypeofBehavior));
		return false;
	}

	UBehavior* behavior = Cast<UBehavior>(InCharacter->GetComponentByClass(TypeofBehavior));

	bool bValidCheck = behavior != nullptr && behavior->IsValidLowLevel() && !behavior->IsPendingKill();
	if (bCheckIsActivated) {
		bValidCheck = bValidCheck && behavior->IsActivated();
	}

	return GetResult(bValidCheck);
}

void FBehaviorRequirement::SetRequirementBehaviorType(TSubclassOf<UBehavior> BehaviorType)
{
	TypeofBehavior = BehaviorType;
}

TSubclassOf<UBehavior> FBehaviorRequirement::GetRequirementBehaviorType() const
{
	return TypeofBehavior;
}

void FBehaviorRequirement::SetCheckIsActivated(bool bFlag)
{
	bCheckIsActivated = bFlag;
}

bool FBehaviorRequirement::GetCheckIsActivated() const
{
	return bCheckIsActivated;
}
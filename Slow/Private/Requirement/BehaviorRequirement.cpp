// Copyright 2020 Team slow. All right reserved.

#include "Requirement/BehaviorRequirement.h"

#include "LogDefine.h"
#include "Component/Behavior.h"
#include "Actor/SlowCharacter.h"

FBehaviorRequirement::FBehaviorRequirement()
{
	bCheckIsActivated = true;
}

bool FBehaviorRequirement::Query(ASlowCharacter* InCharacter)
{
	if (InCharacter == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("FBehaviorRequirement::Query(): InCharacter parameter is null."));
		return false;
	}

	if (TypeofBehavior == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("FBehaviorRequirement::Query(): TypeofBehavior is null."));
		return false;
	}

	UBehavior* behavior = Cast<UBehavior>(InCharacter->GetComponentByClass(TypeofBehavior));

	bool bValidCheck = behavior != nullptr && behavior->IsValidLowLevel() && !behavior->IsPendingKill();
	if (bCheckIsActivated) {
		bValidCheck = bValidCheck && behavior->IsActivated();
	}

	return bValidCheck;
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
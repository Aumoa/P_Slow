// Copyright 2020 Team slow. All right reserved.

#include "Requirement/BehaviorRequirement.h"

#include "LogDefine.h"
#include "Component/Behavior.h"
#include "Actor/SlowCharacter.h"

UBehaviorRequirement::UBehaviorRequirement()
{

}

bool UBehaviorRequirement::Query(ASlowCharacter* InCharacter)
{
	if (InCharacter == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("UBehaviorRequirement::Query(): InCharacter parameter is null."));
		return false;
	}

	if (TypeofBehavior == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("UBehaviorRequirement::Query(): TypeofBehavior is null."));
		return false;
	}

	UBehavior* behavior = Cast<UBehavior>(InCharacter->GetComponentByClass(TypeofBehavior));
	return behavior != nullptr;
}

void UBehaviorRequirement::SetRequirementBehaviorType(TSubclassOf<UBehavior> BehaviorType)
{
	TypeofBehavior = BehaviorType;
}

TSubclassOf<UBehavior> UBehaviorRequirement::GetRequirementBehaviorType() const
{
	return TypeofBehavior;
}
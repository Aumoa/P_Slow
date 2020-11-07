// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "ActorTargetRequirement.h"

class ASlowCharacter;
class UBehavior;

class FBehaviorRequirement : public FActorTargetRequirement
{
private:
	uint8 bCheckIsActivated : 1;

	TSubclassOf<UBehavior> TypeofBehavior;

public:
	FBehaviorRequirement();

	bool SelfCheck() const override;
	bool ActorTargetCheck(AActor* InActor) const override;

	virtual bool Query(ASlowCharacter* InCharacter) const;

	void SetRequirementBehaviorType(TSubclassOf<UBehavior> BehaviorType);
	TSubclassOf<UBehavior> GetRequirementBehaviorType() const;
	void SetCheckIsActivated(bool bFlag);
	bool GetCheckIsActivated() const;
};
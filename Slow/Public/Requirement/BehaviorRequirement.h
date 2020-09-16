// Copyright 2020 Team slow. All right reserved.

#include "CoreMinimal.h"
#include "RequirementBase.h"

class ASlowCharacter;
class UBehavior;

class FBehaviorRequirement : public FRequirementBase
{
private:
	uint8 bCheckIsActivated : 1;

	TSubclassOf<UBehavior> TypeofBehavior;

public:
	FBehaviorRequirement();

	virtual bool Query(ASlowCharacter* InCharacter) const;

	void SetRequirementBehaviorType(TSubclassOf<UBehavior> BehaviorType);
	TSubclassOf<UBehavior> GetRequirementBehaviorType() const;
	void SetCheckIsActivated(bool bFlag);
	bool GetCheckIsActivated() const;
};
// Copyright 2020 Team slow. All right reserved.

#include "CoreMinimal.h"
#include "RequirementBase.h"

#include "BehaviorRequirement.generated.h"

class ASlowCharacter;
class UBehavior;

UCLASS()
class SLOW_API UBehaviorRequirement : public URequirementBase
{
	GENERATED_BODY()

private:
	uint8 bCheckIsActivated : 1;

	TSubclassOf<UBehavior> TypeofBehavior;

public:
	UBehaviorRequirement();

	virtual bool Query(ASlowCharacter* InCharacter);

	void SetRequirementBehaviorType(TSubclassOf<UBehavior> BehaviorType);
	TSubclassOf<UBehavior> GetRequirementBehaviorType() const;
	void SetCheckIsActivated(bool bFlag);
	bool GetCheckIsActivated() const;
};
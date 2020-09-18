// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowStatBasedCharacter.h"

#include "Ability/AbilitySlot.h"

#include "SlowPlayableCharacter.generated.h"

class FAbilitySlot;
class FMoveAbility;

UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

private:
	TSharedPtr<FMoveAbility> MoveAbility;

	FAbilitySlot MouseActionSlot;

protected:
	void BeginPlay() override;

public:
	ASlowPlayableCharacter();
	~ASlowPlayableCharacter();

public:
	void Tick(float DeltaTime) override;
	void OnActionInput(const FName& ActionName, bool bPressed);

private:
	void OnMouseAction(bool bPressed);
};

// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowStatBasedCharacter.h"

#include "Ability/AbilitySlot.h"

#include "SlowPlayableCharacter.generated.h"

class UWeaponManager;
class FAbilitySlot;
class FMoveAbility;


UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

private:
	TSharedPtr<FMoveAbility> MoveAbility;

	FAbilitySlot MouseActionSlot;

	UPROPERTY()
	UWeaponManager *WeaponManager;

protected:
	void BeginPlay() override;

public:
	ASlowPlayableCharacter();
	~ASlowPlayableCharacter();

public:
	void Tick(float DeltaTime) override;
	void OnActionInput(const FName& ActionName, bool bPressed);

	int GetCurrentWeaponNum();
	bool GetSwapAinmState();

	void NewWeaponManager();

private:
	void OnMouseAction(bool bPressed);
	
};

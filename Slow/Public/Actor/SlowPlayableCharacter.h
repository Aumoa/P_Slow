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

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent *Weapon;

	FName WeaponSocket;

	bool IsFindInteractionObject;

protected:
	void BeginPlay() override;

public:
	ASlowPlayableCharacter();
	~ASlowPlayableCharacter();

public:
	void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void OnActionInput(const FName& ActionName, bool bPressed);
	void AddYawInput(float NewAxisValue);
	void AddPitchInput(float NewAxisValue);

	int GetCurrentWeaponNum();
	bool GetSwapAinmState();
	bool GetIsFindInteractionObject();

	void NewWeaponManager();
	void SetWeaponMesh();

private:
	void OnMouseAction(bool bPressed);
	
};

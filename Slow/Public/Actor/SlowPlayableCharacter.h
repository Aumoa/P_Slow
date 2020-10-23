// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowStatBasedCharacter.h"
#include "Ability/AbilitySlot.h"

#include "SlowPlayableCharacter.generated.h"

class UWeaponManager;
class FAbilitySlot;
class FMoveAbility;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

private:
	TSharedPtr<FMoveAbility> MoveAbility;

	FAbilitySlot MouseActionSlot;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;

	UPROPERTY()
	UWeaponManager *WeaponManager;

	

	FName WeaponSocket;

	bool IsFindInteractionObject;

protected:
	void BeginPlay() override;

	void SetControlMode(int32 ControlMode);

public:
	ASlowPlayableCharacter();
	~ASlowPlayableCharacter();

public:
	void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void OnActionInput(const FName& ActionName, bool bPressed);
	

	int GetCurrentWeaponNum();
	bool GetSwapAinmState();
	bool GetIsFindInteractionObject();

	
	void SetWeaponMesh();

private:
	void NewWeaponManager();
	void NewSpringArm();

	void OnMouseAction(bool bPressed);

	void OnMoveForward(float NewAxisValue);
	void OnMoveRight(float NewAxisValue);
	void AddYawInput(float NewAxisValue);
	void AddPitchInput(float NewAxisValue);
};

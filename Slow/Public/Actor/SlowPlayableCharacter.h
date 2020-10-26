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
class UAnimMontage;


UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

private:
	TSharedPtr<FMoveAbility> MoveAbility;

	FAbilitySlot MouseActionSlot;

	UPROPERTY(EditAnyWhere, Category = Camera)
	USpringArmComponent *SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;

	UPROPERTY()
	UWeaponManager *WeaponManager;

	UPROPERTY()
	UAnimMontage *AttackMontage;

	UPROPERTY()
	UAnimInstance *AnimInstance;

	TArray<FName> ComboList;
	int MaxComboCount;
	int ComboCount;

	FName WeaponSocket;

	//��ȣ�ۿ� üũ
	bool IsFindInteractionObject;
	//������ üũ
	bool RollInput;
	//���� ������ üũ
	bool IsAttack;
	//�ߺ� ���� üũ
	bool IsOverlapAttack;
	

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
	
	/// <summary>
	/// ���� ������ �ĺ� ��ȣ�� �����ɴϴ�.
	/// </summary>
	int GetCurrentWeaponNum();

	/// <summary>
	/// �ִϸ��̼� ���� �ĺ� �Ҹ��� �����ɴϴ�.
	/// </summary>
	bool GetSwapAinmState();
	bool GetIsFindInteractionObject();
	bool GetRollAnimState();
	bool GetIsBattle();

	
	void SetWeaponMesh();
	void SetWeaponSocketName();

private:
	void NewWeaponManager();
	void NewSpringArm();

	void OnMouseAction(bool bPressed);
	void OnMouseSelection(bool bPressed);

	void OnPlayerAttack();

	UFUNCTION(BlueprintCallable)
	void OnPlayerAttackEnd();
	UFUNCTION(BlueprintCallable)
	void OnAttackInputChecking();

	void OnMoveForward(float NewAxisValue);
	void OnMoveRight(float NewAxisValue);
	void AddYawInput(float NewAxisValue);
	void AddPitchInput(float NewAxisValue);
};

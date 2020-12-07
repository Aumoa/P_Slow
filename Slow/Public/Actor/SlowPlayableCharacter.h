// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SlowStatBasedCharacter.h"
#include "Ability/AbilitySlot.h"

#include "SlowPlayableCharacter.generated.h"

class UWeaponManager;
class FAbilitySlot;
class FMoveAbility;
class FAttackAbility;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UAnimMontage;
class USlowCombatUIWidget;


UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

private:
	TSharedPtr<FMoveAbility> MoveAbility;
	TSharedPtr<FAttackAbility> AttackAbility;

	FAbilitySlot MouseActionSlot;
	FAbilitySlot MouseSelectionSlot;

	FEquipments Equipment;

	UPROPERTY(EditAnyWhere, Category = Camera)
	USpringArmComponent *SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UCapsuleComponent* Collision_Weapon;

	UPROPERTY(EditAnyWhere, Category = Camera)
	TSubclassOf<UCameraShake> CS_PlayerAttack;

	UPROPERTY()
	UWeaponManager *WeaponManager;

	UPROPERTY()
	UAnimMontage *AttackMontage;

	UPROPERTY()
	TArray<UAnimMontage*> HurtMontages;
	
	UPROPERTY()
	UAnimMontage *RollMontage;

	UPROPERTY()
	UAnimInstance *AnimInstance;

	UPROPERTY()
	USlowCombatUIWidget* MyCombatUIWidget;

	

	FStatModifyLinearEffect *DamageEffect;

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
	//�̹� �������� �־�����?
	bool IsValidAttack;
	bool IsDead;
	bool KillActorOffsetFlag = true;

	float RollTime;
	float RollCost = 22;

	float PlayerKill_ZPos;

	FVector PlayerDirection;

	float AttackCooldown; //���� ��Ÿ��
	float MoveCooldown; //�̵� ��Ÿ��
	float BehaviorCoolDown; //�ൿ ��Ÿ��
	
	FName LastLevelName;

protected:
	void BeginPlay() override;

	void SetControlMode(int32 ControlMode);

public:
	ASlowPlayableCharacter();
	~ASlowPlayableCharacter();

public:
	void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual FEquipments GetCurrentEquipments() const override;
	bool AddFaint(float num) override;
	float GetBehaviorCoolDown() const override;
	void SetBehaviorCoolDown(float num) override;
	void OnActorKill() override;
	
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
	bool GetIsDead() const;

	
	void SetWeaponMesh();
	void SetWeaponSocketName();
	void SetWeaponData();
	void DisableWeapon();

	bool FireInteractionRay(float RayLength = 300.0f);
	void SetKillOffsetState(bool bNewFlag);
	void RefreshKillOffset(bool bAutoWakeup = true);
	FName GetLastLevelName() const;

	UFUNCTION(BlueprintCallable)
	ASlowStatBasedCharacter* GetTarget();
	UFUNCTION(BlueprintCallable)
	bool CreateCombatUIWidget();

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
	UFUNCTION(BlueprintCallable)
	void OnColStartAttack();

	void OnPlayerAttackMontageEnd();

	UFUNCTION()
	void OnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnMoveForward(float NewAxisValue);
	void OnMoveRight(float NewAxisValue);
	void AddYawInput(float NewAxisValue);
	void AddPitchInput(float NewAxisValue);

	FVector GetPlayerDirection();
};

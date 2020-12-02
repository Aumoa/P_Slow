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

	UPROPERTY()
	UWeaponManager *WeaponManager;

	UPROPERTY()
	UAnimMontage *AttackMontage;
	
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

	//상호작용 체크
	bool IsFindInteractionObject;
	//구르기 체크
	bool RollInput;
	//공격 중인지 체크
	bool IsAttack;
	//중복 공격 체크
	bool IsOverlapAttack;
	//이미 데미지를 주었는지?
	bool IsValidAttack;

	float RollTime;

	FVector PlayerDirection;

	float AttackCooldown; //공격 쿨타임
	float MoveCooldown; //이동 쿨타임
	float BehaviorCooldown; //행동 쿨타임
	

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
	
	void OnActionInput(const FName& ActionName, bool bPressed);
	
	/// <summary>
	/// 현재 무기의 식별 번호를 가져옵니다.
	/// </summary>
	int GetCurrentWeaponNum();

	/// <summary>
	/// 애니메이션 스왑 식별 불린을 가져옵니다.
	/// </summary>
	bool GetSwapAinmState();
	bool GetIsFindInteractionObject();
	bool GetRollAnimState();
	bool GetIsBattle();

	
	void SetWeaponMesh();
	void SetWeaponSocketName();
	void SetWeaponData();
	void DisableWeapon();

	bool FireInteractionRay(float RayLength = 300.0f);

	UFUNCTION(BlueprintCallable)
	ASlowStatBasedCharacter* GetTarget();

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
	UFUNCTION()
	void OnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnMoveForward(float NewAxisValue);
	void OnMoveRight(float NewAxisValue);
	void AddYawInput(float NewAxisValue);
	void AddPitchInput(float NewAxisValue);

	FVector GetPlayerDirection();
};

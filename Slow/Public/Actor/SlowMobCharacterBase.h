// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "SlowStatBasedCharacter.h"

#include "SlowMobCharacterBase.generated.h"

class UAnimMontage;
class UBoss1AnimInstance;

UCLASS()
class SLOW_API ASlowMobCharacterBase : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UCapsuleComponent* AttackCollision;

	UPROPERTY()
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY()
	UAnimMontage* FaintMontage;

	UPROPERTY(EditAnyWhere, Category = Camera)
	TSubclassOf<UCameraShake> CS_BossAttack;

	FStatModifyLinearEffect* DamageEffect;


private:
	bool IsAttack;
	bool IsDead;
	bool IsFaint;

	float BehaviorCoolDown;
	float DeltaHP;
	float CumDamageTime;
	FName AttackSocketName;

public:
	ASlowMobCharacterBase();

protected:
	void BeginPlay() override;

public:
	void Tick(float deltaTime) override;
	UFUNCTION()
	void OnHitCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool AddFaint(float num) override;
	float GetBehaviorCoolDown() const override;
	void OnActorKill() override;
	float GetFaintHP() override;

	UFUNCTION(BlueprintCallable)
	bool Monster_Attack();
	UFUNCTION(BlueprintCallable)
	void Monster_AttackEnd();
	
	UBoss1AnimInstance* GetBossAnimInstance();

	UAnimMontage* GetAttackMontage(int FindNum);
	bool GetIsDead() const;
	

	bool PlayMontage(UAnimMontage *montage);
};
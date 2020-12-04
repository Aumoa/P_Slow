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

	FStatModifyLinearEffect* DamageEffect;


private:
	bool IsAttack;
	float MaxAttackDelay = 2.0f;

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

	UFUNCTION(BlueprintCallable)
	bool Monster_Attack();
	UFUNCTION(BlueprintCallable)
	void Monster_AttackEnd();
	
	UBoss1AnimInstance* GetBossAnimInstance();

	UAnimMontage* GetAttackMontage(int FindNum);

	bool PlayMontage(UAnimMontage *montage);
};
// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "SlowStatBasedCharacter.h"

#include "SlowMobCharacterBase.generated.h"


UCLASS()
class SLOW_API ASlowMobCharacterBase : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	UBoxComponent* Collision_Attack;

	FStatModifyLinearEffect* DamageEffect;

private:
	bool IsAttack;
	float MaxAttackDelay = 2.0f;
	float DeltaAttackDelay = 0.0f;

public:
	ASlowMobCharacterBase();

protected:
	void BeginPlay() override;

public:
	void Tick(float deltaTime) override;
	UFUNCTION()
	void OnHitCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool Attack() override;
	
};
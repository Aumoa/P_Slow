// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SlowAnimInstance.h"

#include "Boss1AnimInstance.generated.h"

class ASlowMobCharacterBase;

UCLASS()
class SLOW_API UBoss1AnimInstance : public USlowAnimInstance
{
	GENERATED_BODY()

private:
	mutable TWeakObjectPtr<ASlowMobCharacterBase> LastUpdatedMob;

protected:
	UFUNCTION(BlueprintPure)
	ASlowMobCharacterBase* TryGetLastUpdateMob() const;

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetBoss_IsDead();

};
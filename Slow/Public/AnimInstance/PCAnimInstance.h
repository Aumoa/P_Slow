// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowAnimInstance.h"

#include "PCAnimInstance.generated.h"

class ASlowPlayableCharacter;

UCLASS()
class SLOW_API UPCAnimInstance : public USlowAnimInstance
{
	GENERATED_BODY()

private:
	mutable TWeakObjectPtr<ASlowPlayableCharacter> LastUpdatedPC;

protected:
	UFUNCTION(BlueprintPure)
	ASlowPlayableCharacter* TryGetLastUpdatedPC() const;

public:
	UPCAnimInstance();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
};
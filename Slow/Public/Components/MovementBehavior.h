// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "Behavior.h"

#include "MovementBehavior.generated.h"

class UCharacterMovementComponent;

UCLASS()
class SLOW_API UMovementBehavior : public UBehavior
{
	GENERATED_BODY()

private:
	uint8 bDirtyMark : 1;
	uint8 bUseNavigationPath : 1;

	TWeakObjectPtr<ACharacter> MyOwner;
	TWeakObjectPtr<UCharacterMovementComponent> MyMovementComponent;

	TArray<FVector> MovementPaths;
	FVector Goal;
	FVector LastDirection;

	float ScaledCapsuleRadius = 0;

public:
	UMovementBehavior();

	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetActorDestination(const FVector& Dest, bool bFindNavigationPath = true);

private:
	void RebuildPaths();
	bool AddMove();
};
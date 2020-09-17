// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
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

	TWeakObjectPtr<UCharacterMovementComponent> MovementActor;

	TArray<FVector> MovementPaths;
	FVector Goal;
	FVector LastDirection;

public:
	UMovementBehavior();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMovementActor(UCharacterMovementComponent* InMovementActor);
	UCharacterMovementComponent* GetMovementActor() const;

	void SetActorDestination(const FVector& Dest, bool bFindNavigationPath = false);

private:
	void RebuildPaths();
	void AddMove(float DeltaTime);
};
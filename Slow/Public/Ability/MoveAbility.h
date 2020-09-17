// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "ILocationTargetAbility.h"
#include "IActorTargetAbility.h"

class ASlowStatBasedCharacter;
class UCharacterMovementComponent;

class FMoveAbility : virtual public FAbilityBase, virtual public ILocationTargetAbility, virtual public IActorTargetAbility
{
	enum class ETargetType
	{
		Location,
		Actor,
	};

private:
	TWeakObjectPtr<ASlowStatBasedCharacter> CastPlayer;
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

	ETargetType TargetType;
	FVector LocationTarget;
	TWeakObjectPtr<AActor> ActorTarget;

public:
	FMoveAbility();

	void ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer) override;
	void SetTarget(const FVector& InLocation) override;
	void SetTarget(AActor* InActor) override;
};
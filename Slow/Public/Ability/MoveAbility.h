// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "BehaviorAbility.h"
#include "ILocationTargetAbility.h"

class ASlowStatBasedCharacter;
class UCharacterMovementComponent;
class UMovementBehavior;

class FMoveAbility : public FBehaviorAbility<UMovementBehavior>, virtual public ILocationTargetAbility
{
	enum class ETargetType
	{
		Unknown,
		Location,
	};

	using LocationMoveAbil = FBehaviorAbility<UMovementBehavior>;

private:
	TWeakObjectPtr<ASlowStatBasedCharacter> CastPlayer;
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

	ETargetType TargetType = ETargetType::Unknown;

public:
	FMoveAbility();

	bool ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer) override;
	void SetTarget(const FVector& InLocation) override;

private:
	void Clear();
};
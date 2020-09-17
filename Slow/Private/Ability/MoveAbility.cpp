// Copyright 2020 Team slow. All right reserved.

#include "Ability/MoveAbility.h"

#include "LogDefine.h"
#include "Actor/SlowStatBasedCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"

FMoveAbility::FMoveAbility()
{

}

void FMoveAbility::ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer)
{
	CastPlayer = InCastPlayer;
	MovementComponent = Cast<UCharacterMovementComponent>(InCastPlayer->GetMovementComponent());

	if (MovementComponent == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("FMoveAbility::ExecuteIndirect(): InCastPlayer must have UCharacterMovementComponent but there is no."));
	}
}

void FMoveAbility::SetTarget(const FVector& InLocation)
{
	LocationTarget = InLocation;
	TargetType = ETargetType::Location;
}

void FMoveAbility::SetTarget(AActor* InActor)
{
	ActorTarget = InActor;
	TargetType = ETargetType::Actor;
}
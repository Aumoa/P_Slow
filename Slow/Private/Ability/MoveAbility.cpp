// Copyright 2020 Team slow. All right reserved.

#include "Ability/MoveAbility.h"

#include "LogDefine.h"
#include "Actor/SlowStatBasedCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MovementBehavior.h"

FMoveAbility::FMoveAbility()
{

}

bool FMoveAbility::ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer)
{
	CastPlayer = InCastPlayer;
	MovementComponent = Cast<UCharacterMovementComponent>(InCastPlayer->GetMovementComponent());

	if (MovementComponent == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("FMoveAbility::ExecuteIndirect(): InCastPlayer must have UCharacterMovementComponent but there is no."));
		return false;
	}

	return true;
}

void FMoveAbility::SetTarget(const FVector& InLocation)
{
	Clear();

	UMovementBehavior* behavior = LocationMoveAbil::AttachTo(CastPlayer.Get());
	if (behavior != nullptr) {
		behavior->SetActorDestination(InLocation, true);
	}

	
}

void FMoveAbility::Clear()
{
	switch (TargetType) {
	case ETargetType::Location:
		LocationMoveAbil::RemoveFrom(CastPlayer.Get());
		break;
	}
}
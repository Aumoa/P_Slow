// Copyright 2020 Team slow. All right reserved.

#include "Ability/MoveAbility.h"

#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"
#include "Actor/SlowStatBasedCharacter.h"

FMoveAbility::FMoveAbility()
{

}

bool FMoveAbility::ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer)
{
	CastPlayer = InCastPlayer;
	MovementComponent = Cast<UCharacterMovementComponent>(InCastPlayer->GetMovementComponent());

	if (MovementComponent == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("%s: %s must have UCharacterMovementComponent but there is no."), __FUNCTIONT__, nameof(InCastPlayer), nameof_c(UCharacterMovementComponent));
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
// Copyright 2020 Team slow. All right reserved.

#include "AnimInstance/PCAnimInstance.h"

#include "Actor/SlowPlayableCharacter.h"

ASlowPlayableCharacter* UPCAnimInstance::TryGetLastUpdatedPC() const
{
	if (!LastUpdatedPC.IsValid()) {
		APawn* owner = TryGetPawnOwner();
		if (owner == nullptr) {
			return nullptr;
		}

		auto pc = Cast<ASlowPlayableCharacter>(owner);
		if (pc == nullptr) {
			return nullptr;
		}

		LastUpdatedPC = pc;
	}

	return LastUpdatedPC.Get();
}

UPCAnimInstance::UPCAnimInstance()
{

}

void UPCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	TryGetLastUpdatedPC();
}

void UPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
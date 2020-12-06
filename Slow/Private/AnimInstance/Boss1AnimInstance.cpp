// Copyright 2020 Team slow. All right reserved.

#include "AnimInstance/Boss1AnimInstance.h"
#include "Actor/SlowMobCharacterBase.h"

ASlowMobCharacterBase* UBoss1AnimInstance::TryGetLastUpdateMob() const
{
	if (!LastUpdatedMob.IsValid()) {
		APawn* owner = TryGetPawnOwner();
		if (owner == nullptr) {
			return nullptr;
		}

		auto monster = Cast<ASlowMobCharacterBase>(owner);
		if (monster == nullptr) {
			return nullptr;
		}
		LastUpdatedMob = monster;
	}

	return LastUpdatedMob.Get();
}

void UBoss1AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	TryGetLastUpdateMob();
}

void UBoss1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

bool UBoss1AnimInstance::GetBoss_IsDead()
{
	if (LastUpdatedMob == nullptr)
	{
		return false;
	}

	return LastUpdatedMob->GetIsDead();
}
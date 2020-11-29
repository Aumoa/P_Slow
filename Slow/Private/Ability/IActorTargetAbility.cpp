// Copyright 2020 Team slow. All right reserved.

#include "Ability/IActorTargetAbility.h"

IActorTargetAbility::IActorTargetAbility()
{

}

TWeakObjectPtr<ASlowCharacter> IActorTargetAbility::GetTarget()
{
	return nullptr;
}


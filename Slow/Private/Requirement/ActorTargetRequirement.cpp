// Copyright 2020 Team slow. All right reserved.

#include "Requirement/ActorTargetRequirement.h"

FActorTargetRequirement::FActorTargetRequirement()
{

}

bool FActorTargetRequirement::ActorTargetCheck(AActor* InActor) const
{
	return true;
}
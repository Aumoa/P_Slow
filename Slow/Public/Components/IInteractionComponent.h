// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "IInteractionComponent.generated.h"

class AActor;

UINTERFACE()
class SLOW_API UInteractionComponent : public UInterface
{
	GENERATED_BODY()
};

class SLOW_API IInteractionComponent
{
	GENERATED_BODY()

public:
	virtual bool OnHitInteractionRay(AActor* InEventSender, FHitResult& InRemoteHitResult) = 0;
};
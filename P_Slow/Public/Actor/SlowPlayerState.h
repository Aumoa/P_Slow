// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "SlowPlayerState.generated.h"

class USlowPlayableCharacterState;

UCLASS()
class P_SLOW_API ASlowPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY( BlueprintReadWrite ) USlowPlayableCharacterState* PC;
};

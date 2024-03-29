// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "SlowPlayerState.generated.h"

class USlowPlayableCharacterState;

UCLASS()
class SLOW_API ASlowPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY( BlueprintReadWrite ) USlowPlayableCharacterState* PC;
};

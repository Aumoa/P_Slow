// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "SlowPlayableCharacter.generated.h"

class UInputComponent;

UCLASS()
class P_SLOW_API ASlowPlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlowPlayableCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float DeltaTime ) override;
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;
};

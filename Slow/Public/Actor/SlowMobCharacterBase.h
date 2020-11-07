// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "SlowStatBasedCharacter.h"

#include "SlowMobCharacterBase.generated.h"

UCLASS()
class SLOW_API ASlowMobCharacterBase : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

public:
	ASlowMobCharacterBase();

protected:
	void BeginPlay() override;

public:
	void Tick(float deltaTime) override;
};
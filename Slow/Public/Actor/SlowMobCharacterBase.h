// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/SlowCharacter.h"

#include "SlowMobCharacterBase.generated.h"

class UStatComponent;

UCLASS()
class SLOW_API ASlowMobCharacterBase : public ASlowCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UStatComponent* StatComponent;

public:
	ASlowMobCharacterBase();

protected:
	void BeginPlay() override;

public:
	void Tick(float deltaTime) override;
};
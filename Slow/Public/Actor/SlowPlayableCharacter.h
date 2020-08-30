// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/SlowCharacter.h"

#include "SlowPlayableCharacter.generated.h"

class UInputComponent;
class APlayerController;
class UStatComponent;

UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UStatComponent* StatComponent;

public:
	ASlowPlayableCharacter();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
	void OnActionInput(const FName& ActionName, bool bPressed);

private:
	void OnMouseAction(bool bPressed);
};

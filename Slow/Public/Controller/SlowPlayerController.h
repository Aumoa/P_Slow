// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowControllerBase.h"

#include "SlowPlayerController.generated.h"

class USlowGameInstance;
class UInputComponent;
class ASlowPlayableCharacter;

UCLASS()
class SLOW_API ASlowPlayerController : public ASlowControllerBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASlowPlayableCharacter* Possessed;

public:
	ASlowPlayerController();
	
public:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void OnPossess(APawn* Target) override;
	void OnUnPossess() override;

private:
	void OnMouseActionPressed();
	void OnWeaponSwapPressed();
};

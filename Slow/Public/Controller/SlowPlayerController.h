// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SlowPlayerController.generated.h"

class USlowGameInstance;
class UInputComponent;
class ASlowPlayableCharacter;

UCLASS()
class SLOW_API ASlowPlayerController : public APlayerController
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
	void OnWeaponSwapButtonPressed();
	void OnInteractionButtonPressed();
	void OnRollButtonPressed();
};

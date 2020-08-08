// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SlowPlayerController.generated.h"

class USlowGameInstance;
class UInputComponent;
class ASlowCharacter;

UCLASS()
class P_SLOW_API ASlowPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASlowCharacter* Possessed;

public:
	ASlowPlayerController();
	
public:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void OnPossess(APawn* Target) override;
	void OnUnPossess() override;

private:
	void OnIntroNextSceneInputPressed();
	void OnMouseActionPressed();
};

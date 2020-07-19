// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "SlowPlayerController.generated.h"

class USlowGameInstance;
class UInputComponent;

UCLASS()
class P_SLOW_API ASlowPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY() USlowGameInstance* GameInstance;
	
public:
	void BeginPlay() override;

	UFUNCTION( BlueprintCallable ) virtual void OnIntroNextSceneInput( bool bPressed, const FKey& Key );
};

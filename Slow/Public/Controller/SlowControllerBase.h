// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SlowControllerBase.generated.h"

UCLASS()
class SLOW_API ASlowControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	ASlowControllerBase();

	void BeginPlay() override;
};
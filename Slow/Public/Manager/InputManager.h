// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "ManagerBase.h"

#include "InputManager.generated.h"

class APlayerController;

UCLASS()
class SLOW_API UInputManager : public UManagerBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APlayerController* PlayerController = nullptr;

public:
	static void SetPlayerController(APlayerController* playerController);

private:
	static UInputManager* GetSingletonInstance();
};
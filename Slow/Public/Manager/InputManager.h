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
	static UInputManager* SingletonInstance;

	UPROPERTY()
	APlayerController* PlayerController = nullptr;

public:
	void Initialize(USlowGameInstance* GInstance) override;

	void SetPlayerController(APlayerController* playerController);

	static UInputManager* GetInstance();
};

#define INPUT_MANAGER (*UInputManager::GetInstance())
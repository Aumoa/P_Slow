// Copyright 2020 Team slow. All right reserved.

#include "CoreMinimal.h"
#include "ManagerBase.h"

#include "InputManager.generated.h"

class APlayerController;

UCLASS()
class P_SLOW_API UInputManager : public UManagerBase
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
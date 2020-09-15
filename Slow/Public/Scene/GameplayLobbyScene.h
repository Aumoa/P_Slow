// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayScene.h"

#include "GameplayLobbyScene.generated.h"

class ASlowControllerBase;
class APawn;

UCLASS()
class SLOW_API UGameplayLobbyScene : public UGameplayScene
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APawn* TempSpawn;

public:
	void BeginPlay(UObject* Args = nullptr) override;
	void BeginLevel(ASlowControllerBase* InPlayerController) override;
	void EndPlay() override;
};
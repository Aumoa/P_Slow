// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayScene.h"

#include "GameplayStage01Scene.generated.h"

UCLASS()
class SLOW_API UGameplayStage01Scene : public UGameplayScene
{
	GENERATED_BODY()

private:

public:
	void BeginPlay(UObject* Args = nullptr) override;
	void BeginLevel(ASlowPlayerController* InPlayerController) override;
	void EndPlay() override;
};
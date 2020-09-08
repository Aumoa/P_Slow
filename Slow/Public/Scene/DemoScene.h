// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Scene/SceneBase.h"

#include "DemoScene.generated.h"

class USlowGameInstance;

UCLASS()
class SLOW_API UDemoScene : public USceneBase
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<USlowGameInstance> GameInstance;

	int64 MyWidgetLuid = 0;

public:
	void BeginPlay( UObject* Args = nullptr ) override;
	void BeginLevel(ASlowControllerBase* InPlayerController) override;
	void EndPlay() override;

	UFUNCTION( BlueprintCallable ) void OnDemoEnded();

private:
	void OpenNextScene();
};

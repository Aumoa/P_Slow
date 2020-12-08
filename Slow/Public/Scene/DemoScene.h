// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "Scene/SceneBase.h"

#include "DemoScene.generated.h"

class USlowGameInstance;
class UDemoWidget;

UCLASS()
class SLOW_API UDemoScene : public USceneBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UDemoWidget* MyWidget;

public:
	UDemoScene();

	void BeginPlay( UObject* Args = nullptr ) override;
	void BeginLevel(ASlowPlayerController* InPlayerController) override;
	void EndPlay() override;

	UFUNCTION( BlueprintCallable ) void OnDemoEnded();
};

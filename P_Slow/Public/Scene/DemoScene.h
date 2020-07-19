// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Scene/SceneBase.h"

#include "DemoScene.generated.h"

class USlowGameInstance;

UCLASS()
class P_SLOW_API UDemoScene : public USceneBase
{
	GENERATED_BODY()

private:
	UPROPERTY() USlowGameInstance* GameInstance;

public:
	void BeginPlay( UObject* Args = nullptr ) override;
	void EndPlay() override;

	UFUNCTION( BlueprintCallable ) void OnDemoEnded();

private:
	void OpenNextScene();
};

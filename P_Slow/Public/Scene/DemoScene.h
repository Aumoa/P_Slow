// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Scene/SceneBase.h"

#include "DemoScene.generated.h"

/**
 * 
 */
UCLASS()
class P_SLOW_API UDemoScene : public USceneBase
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void EndPlay() override;

private:
	void OpenNextScene();
};

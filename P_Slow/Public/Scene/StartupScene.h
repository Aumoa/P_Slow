// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Scene/SceneBase.h"
#include "StartupScene.generated.h"

/**
 * 
 */
UCLASS()
class P_SLOW_API UStartupScene : public USceneBase
{
	GENERATED_BODY()
	
public:
	void BeginPlay( UObject* Args = nullptr ) override;
	void EndPlay() override;

private:
	void OpenDemoScene();
};

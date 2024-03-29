// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "Scene/SceneBase.h"

#include "StartupScene.generated.h"

UCLASS()
class SLOW_API UStartupScene : public USceneBase
{
	GENERATED_BODY()
	
public:
	UStartupScene();

	void BeginPlay(UObject* Args = nullptr) override;
	void EndPlay() override;

private:
	void OpenDemoScene();
};

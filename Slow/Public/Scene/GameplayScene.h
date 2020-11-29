// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "Scene/SceneBase.h"

#include "GameplayScene.generated.h"

class USlowCombatUIWidget;

UCLASS()
class SLOW_API UGameplayScene : public USceneBase
{
	GENERATED_BODY()
	
private:
	

public:
	UGameplayScene();

	void BeginPlay(UObject* Args = nullptr) override;
	void EndPlay() override;

private:
	
};

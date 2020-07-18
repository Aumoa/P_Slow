// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Scene/SceneBase.h"
#include "IntroScene.generated.h"

/**
 * 
 */
UCLASS()
class P_SLOW_API UIntroScene : public USceneBase
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void EndPlay() override;
};

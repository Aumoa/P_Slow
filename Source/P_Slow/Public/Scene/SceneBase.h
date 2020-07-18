// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "SceneBase.generated.h"

/**
 * 
 */
UCLASS()
class P_SLOW_API USceneBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION() virtual void BeginPlay();
	UFUNCTION() virtual void EndPlay();
};

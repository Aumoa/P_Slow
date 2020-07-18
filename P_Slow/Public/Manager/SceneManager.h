// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "SceneManager.generated.h"

class USceneBase;

/**
 * 
 */
UCLASS()
class P_SLOW_API USceneManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY() USceneBase* CurrentScene;

	UPROPERTY() USceneBase* StartupScene;

public:
	UFUNCTION() void Initialize();

	UFUNCTION() void LoadScene( const FString& SceneName );
	UFUNCTION() USceneBase* GetCurrentScene() const;
};

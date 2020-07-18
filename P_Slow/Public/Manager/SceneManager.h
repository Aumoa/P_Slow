// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "SceneManager.generated.h"

class USlowGameInstance;

class USceneBase;
class UStartupScene;
class UDemoScene;
class UIntroScene;

/**
 * 
 */
UCLASS()
class P_SLOW_API USceneManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY() USceneBase* CurrentScene;

	UPROPERTY() UStartupScene* StartupScene;
	UPROPERTY() UDemoScene* DemoScene;
	UPROPERTY() UIntroScene* IntroScene;

public:
	UFUNCTION() void Initialize( USlowGameInstance* GInstance );

	UFUNCTION( BlueprintCallable ) void LoadScene( const FString& SceneName );
	UFUNCTION( BlueprintCallable ) USceneBase* GetCurrentScene() const;

private:
	USceneBase* GetSceneByName( const FString& SceneName, bool& bChanged ) const;
};

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
class UGameplayScene;

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
	UPROPERTY() USceneBase* DemoScene;
	UPROPERTY() USceneBase* IntroScene;
	UPROPERTY() USceneBase* GameplayScene;

public:
	UFUNCTION() void Initialize( USlowGameInstance* GInstance );

	UFUNCTION( BlueprintCallable, Category = "SceneManager" ) static void LoadScene( UObject* This, const FString& SceneName, UObject* Args = nullptr );
	UFUNCTION( BlueprintCallable, Category = "SceneManager" ) static USceneBase* GetCurrentScene( UObject* This );

private:
	static USceneBase* GetSceneByName( USceneManager* Instance, const FString& SceneName, bool& bChanged );
	static USceneManager* GetSingletonInstance( UObject* This );
};

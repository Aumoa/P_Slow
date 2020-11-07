// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "ManagerBase.h"

#include "SceneManager.generated.h"

class USlowGameInstance;

class USceneBase;
class UStartupScene;
class UDemoScene;
class UIntroScene;
class UGameplayScene;
class ULevel;
class UWorld;
class ASlowPlayerController;

UCLASS()
class SLOW_API USceneManager : public UManagerBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY() USceneBase* CurrentScene;

	UPROPERTY() USceneBase* StartupScene;
	UPROPERTY() USceneBase* DemoScene;
	UPROPERTY() USceneBase* IntroScene;
	UPROPERTY() USceneBase* GameplayScene;

public:
	void Initialize(USlowGameInstance* GInstance) override;

	static void BeginLevel(ASlowPlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	static void LoadScene(const FString& SceneName, UObject* Args = nullptr);
	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	static void SwitchScene(USceneBase* InNextScene, UObject* Args = nullptr);
	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	static USceneBase* GetCurrentScene();
	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	static void SendInputAction(const FName& ActionName, bool bPressed);


private:
	static USceneBase* GetSceneByName( USceneManager* Instance, const FString& SceneName, bool& bChanged );
	static USceneManager* GetSingletonInstance();
};

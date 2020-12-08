// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "ManagerBase.h"

#include "SceneManager.generated.h"

class USlowGameInstance;

class USceneBase;
class ASlowPlayerController;

UCLASS()
class SLOW_API USceneManager : public UManagerBase
{
	GENERATED_BODY()
	
private:
	static USceneManager* SingletonInstance;

	UPROPERTY()
	USceneBase* CurrentScene;

public:
	void Initialize(USlowGameInstance* GInstance) override;

	void BeginLevel(ASlowPlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	void SwitchScene(USceneBase* InNextScene, UObject* Args = nullptr);
	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	USceneBase* GetCurrentScene();
	UFUNCTION(BlueprintCallable, Category = "SceneManager")
	void SendInputAction(const FName& ActionName, bool bPressed);

	static USceneManager* GetInstance();
};

#define SCENE_MANAGER (*USceneManager::GetInstance())
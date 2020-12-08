// Copyright 2020 Team slow. All right reserved.

#include "Manager/SceneManager.h"

#include "SlowGameInstance.h"
#include "Common/SlowLogDefine.h"
#include "Manager/ConfigManager.h"
#include "Scene/StartupScene.h"

USceneManager* USceneManager::SingletonInstance = nullptr;

void USceneManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	SingletonInstance = this;
}

void USceneManager::BeginLevel(ASlowPlayerController* InPlayerController)
{
	if (CurrentScene != nullptr) {
		CurrentScene->BeginLevel(InPlayerController);
	}
	else {
		SwitchScene(NewObject<UStartupScene>(this));
	}
}

void USceneManager::SwitchScene(USceneBase* InNextScene, UObject* Args)
{
	bool bChanged = false;

	if (CurrentScene != nullptr) {
		CurrentScene->EndPlay();
	}

	CurrentScene = InNextScene;
	bChanged = true;
	
	if (bChanged) {
		CurrentScene->BeginPlay(Args);
	}
}

USceneBase* USceneManager::GetCurrentScene()
{
	return CurrentScene;
}

void USceneManager::SendInputAction(const FName& ActionName, bool bPressed)
{
	return CurrentScene->OnActionInput(ActionName, bPressed);
}

USceneManager* USceneManager::GetInstance()
{
	return SingletonInstance;
}
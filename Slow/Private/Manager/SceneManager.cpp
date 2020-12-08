// Copyright 2020 Team slow. All right reserved.

#include "Manager/SceneManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "Common/SlowLogDefine.h"

USceneManager* USceneManager::SingletonInstance = nullptr;

void USceneManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	auto Config = GInstance->GetConfig();

	StartupScene = NewObject<USceneBase>(this, Config->StartupScene);
	DemoScene = NewObject<USceneBase>(this, Config->DemoScene);
	IntroScene = NewObject<USceneBase>(this, Config->IntroScene);

	SingletonInstance = this;
}

void USceneManager::BeginLevel(ASlowPlayerController* InPlayerController)
{
	if (CurrentScene != nullptr) {
		CurrentScene->BeginLevel(InPlayerController);
	}
	else {
		LoadScene(GetGameInstance()->GetConfig()->EntryPoint);
	}
}

void USceneManager::LoadScene(const FString& SceneName, UObject* Args)
{
	bool bChanged = false;

	if (CurrentScene != nullptr) {
		CurrentScene->EndPlay();
	}

	CurrentScene = GetSceneByName(SceneName, bChanged);

	if (bChanged) {
		CurrentScene->BeginPlay(Args);
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

USceneBase* USceneManager::GetSceneByName(const FString& SceneName, bool& bChanged)
{
	USceneBase* NextScene = nullptr;
	bChanged = false;

	if (SceneName == TEXT("Startup")) {
		NextScene = StartupScene;
	}
	else if (SceneName == TEXT("Demo")) {
		NextScene = DemoScene;
	}
	else if (SceneName == TEXT("Intro")) {
		NextScene = IntroScene;
	}
	else if (SceneName == TEXT("Gameplay")) {
		NextScene = GameplayScene;
	}
	else if (SceneName == TEXT("Map_1S")) {
		NextScene = GameplayScene;
	}

	else {
		UE_LOG(LogSlow, Error, TEXT("Scene name: [%s] is not registered."), *SceneName);
		return CurrentScene;
	}

	if (CurrentScene != NextScene) {
		bChanged = true;
	}

	return NextScene;
}
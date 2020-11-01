// Copyright 2020 Team slow. All right reserved.

#include "Manager/SceneManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "Common/SlowLogDefine.h"

#include "Kismet/GameplayStatics.h"

void USceneManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	auto Config = GInstance->GetConfig();

	StartupScene = NewObject<USceneBase>(this, Config->StartupScene);
	DemoScene = NewObject<USceneBase>(this, Config->DemoScene);
	IntroScene = NewObject<USceneBase>(this, Config->IntroScene);
}

void USceneManager::BeginLevel(ASlowPlayerController* InPlayerController)
{
	auto Instance = GetSingletonInstance();

	if (Instance->CurrentScene != nullptr) {
		Instance->CurrentScene->BeginLevel(InPlayerController);
	}
	else {
		LoadScene(GetGameInstance()->GetConfig()->EntryPoint);
	}
}

void USceneManager::LoadScene(const FString& SceneName, UObject* Args)
{
	auto Instance = GetSingletonInstance();

	bool bChanged = false;

	if (Instance->CurrentScene != nullptr) {
		Instance->CurrentScene->EndPlay();
	}

	Instance->CurrentScene = GetSceneByName(Instance, SceneName, bChanged);

	if (bChanged) {
		Instance->CurrentScene->BeginPlay(Args);
	}
}

void USceneManager::SwitchScene(USceneBase* InNextScene, UObject* Args)
{
	auto Instance = GetSingletonInstance();
	bool bChanged = false;

	if (Instance->CurrentScene != nullptr) {
		Instance->CurrentScene->EndPlay();
	}

	if (Instance->CurrentScene != InNextScene) {
		Instance->CurrentScene = InNextScene;
		bChanged = true;
	}

	if (bChanged) {
		Instance->CurrentScene->BeginPlay(Args);
	}
}

USceneBase* USceneManager::GetCurrentScene()
{
	return GetSingletonInstance()->CurrentScene;
}

void USceneManager::SendInputAction(const FName& ActionName, bool bPressed)
{
	return GetSingletonInstance()->CurrentScene->OnActionInput(ActionName, bPressed);
}

USceneBase* USceneManager::GetSceneByName(USceneManager* Instance, const FString& SceneName, bool& bChanged)
{
	USceneBase* NextScene = nullptr;
	bChanged = false;

	if (SceneName == TEXT("Startup")) {
		NextScene = Instance->StartupScene;
	}
	else if (SceneName == TEXT("Demo")) {
		NextScene = Instance->DemoScene;
	}
	else if (SceneName == TEXT("Intro")) {
		NextScene = Instance->IntroScene;
	}
	else if (SceneName == TEXT("Gameplay")) {
		NextScene = Instance->GameplayScene;
	}
	else if (SceneName == TEXT("Map_1S")) {
		NextScene = Instance->GameplayScene;
	}

	else {
		UE_LOG(LogSlow, Error, TEXT("Scene name: [%s] is not registered."), *SceneName);
		return Instance->CurrentScene;;
	}

	if (Instance->CurrentScene != NextScene) {
		bChanged = true;
	}

	return NextScene;
}

USceneManager* USceneManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<USceneManager>();
}
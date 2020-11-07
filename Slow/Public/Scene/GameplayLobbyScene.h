// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "GameplayScene.h"

#include "GameplayLobbyScene.generated.h"

class APawn;
class ASlowPlayerController;

UCLASS()
class SLOW_API UGameplayLobbyScene : public UGameplayScene
{
	GENERATED_BODY()

private:
	uint8 bStreamLoaded_Base : 1;

	UPROPERTY()
	APawn* TempSpawn;

	TUniquePtr<FCriticalSection> StreamLoadCS;

public:
	UGameplayLobbyScene();

	void BeginPlay(UObject* Args = nullptr) override;
	void BeginLevel(ASlowPlayerController* InPlayerController) override;
	void EndPlay() override;

	virtual void OnStreamLoaded();

private:
	UFUNCTION()
	void OnStreamLoaded_Base();

	void OnStreamLoaded_CheckAndInvoke();
};
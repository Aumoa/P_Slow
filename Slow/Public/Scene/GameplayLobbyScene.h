// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "GameplayScene.h"

#include "GameplayLobbyScene.generated.h"

class APawn;
class ASlowPlayerController;
class ULevelStreamingStatics;

UCLASS()
class SLOW_API UGameplayLobbyScene : public UGameplayScene
{
	GENERATED_BODY()

private:
	uint8 bStreamLoaded_Base : 1;
	uint8 bStreamLoaded_Boss1 : 1;

	UPROPERTY()
	APawn* TempSpawn;
	UPROPERTY()
	ULevelStreamingStatics* LevelStreamingStatics;

	TOptional<float> SavedGravityScale;
	static FName LastLevelName;

public:
	UGameplayLobbyScene();

	void BeginPlay(UObject* Args = nullptr) override;
	void BeginLevel(ASlowPlayerController* InPlayerController) override;
	void EndPlay() override;
	
	void MigrateLevelGroup(FName LevelGroupName);
	void ReloadLevels();

	FName GetCurrentLevelName() const;

protected:
	virtual void OnStreamLoaded(bool bReinitCharacter = false);

private:
	void BeginLoadLevel();
	void EndLoadLevel();
};
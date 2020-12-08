// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SceneBase.generated.h"

class ULevel;
class UWorld;
class ASlowPlayerController;
class ULevelStreamingStatics;

UCLASS(Blueprintable, abstract)
class SLOW_API USceneBase : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(USceneBase, SublevelGroupLoadedEvent);

private:
	TWeakObjectPtr<ASlowPlayerController> PlayerController;

	UPROPERTY()
	ULevelStreamingStatics* LevelStreaming;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected = "true"))
	uint8 bCursorVisibleOverride : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected = "true"))
	FName PersistentLevelName;

public:
	USceneBase();

	virtual void BeginPlay(UObject* Args = nullptr);
	virtual void BeginLevel(ASlowPlayerController* InPlayerController);
	virtual void EndPlay();

	virtual void OnActionInput(const FName& ActionName, bool bPressed);

	bool GetCursorVisibleOverride() const;
	ASlowPlayerController* GetCurrentPlayerController() const;

	SublevelGroupLoadedEvent SublevelGroupLoaded;

protected:
	void LoadSublevelGroup(FName SublevelGroup);
};
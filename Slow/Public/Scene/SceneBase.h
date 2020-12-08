// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SceneBase.generated.h"

class ULevel;
class UWorld;
class ASlowPlayerController;

UCLASS(Blueprintable, abstract)
class SLOW_API USceneBase : public UObject
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<ASlowPlayerController> PlayerController;

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
};
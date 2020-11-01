// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Misc/KeepRelative.h"

#include "SceneBase.generated.h"

class ULevel;
class UWorld;
class ASlowPlayerController;

UCLASS(Blueprintable)
class SLOW_API USceneBase : public UObject
{
	GENERATED_BODY()

private:
	uint8 bCursorVisibleOverride : 1;

public:
	USceneBase();

	virtual void BeginPlay(UObject* Args = nullptr);
	virtual void BeginLevel(ASlowPlayerController* InPlayerController);
	virtual void EndPlay();

	virtual void OnActionInput(const FName& ActionName, bool bPressed);

	bool GetCursorVisibleOverride() const;
	APlayerController* GetCurrentPlayerController() const;

protected:
	void SetCursorVisibleOverride(bool bVisible);
};
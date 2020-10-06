// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "SceneBase.generated.h"

class ULevel;
class UWorld;
class ASlowPlayerController;

UCLASS(Blueprintable)
class SLOW_API USceneBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginPlay(UObject* Args = nullptr);
	virtual void BeginLevel(ASlowPlayerController* InPlayerController);
	virtual void EndPlay();

	virtual void OnActionInput(const FName& ActionName, bool bPressed);
};

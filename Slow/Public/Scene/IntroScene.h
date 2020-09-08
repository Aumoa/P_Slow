// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Scene/SceneBase.h"
#include "IntroScene.generated.h"

class UIntroWidget;

UCLASS()
class SLOW_API UIntroScene : public USceneBase
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<UIntroWidget> MyMainWidget;
	int64 MyMainWidgetLuid = 0;

public:
	void BeginPlay(UObject* Args = nullptr) override;
	void BeginLevel(ASlowControllerBase* InPlayerController) override;
	void EndPlay() override;

	void OnActionInput(const FName& ActionName, bool bPressed) override;

private:
	void OnIntroNextSceneInput();
};

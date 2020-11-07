// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "Scene/SceneBase.h"

#include "IntroScene.generated.h"

class UIntroWidget;

UCLASS()
class SLOW_API UIntroScene : public USceneBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UIntroWidget* MyMainWidget;

public:
	void BeginPlay(UObject* Args = nullptr) override;
	void BeginLevel(ASlowPlayerController* InPlayerController) override;
	void EndPlay() override;

	void OnActionInput(const FName& ActionName, bool bPressed) override;

private:
	void OnIntroNextSceneInput();
};

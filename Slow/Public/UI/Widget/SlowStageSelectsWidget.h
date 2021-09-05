// Copyright 2020. Team slow, All right reserved.
#pragma once


#include "UI/SlowWidgetBase.h"

#include "SlowStageSelectsWidget.generated.h"

class USlowTextButton;
class USceneBase;

UCLASS()
class SLOW_API USlowStageSelectsWidget : public USlowWidgetBase
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(USlowStageSelectsWidget, FDisposingEvent);

private:
	UPROPERTY(meta = (BindWidget))
	USlowTextButton* Button_Stage1_1;
	UPROPERTY(meta = (BindWidget))
	USlowTextButton* Button_Stage1_2;
	/*UPROPERTY(meta = (BindWidget))
	USlowTextButton* Button_Stage1_3;*/

	UPROPERTY(meta = (BindWidget))
	USlowTextButton* Button_Cancel;

	UPROPERTY()
	USceneBase* NextScene = nullptr;

public:
	void NativeConstruct() override;

	USceneBase* GetNextScene() const;

	FDisposingEvent Disposing;

private:
	void OnClicked_Stage1_1(USlowTextButton* InClickedButton);
	void OnClicked_Stage1_2(USlowTextButton* InClickedButton);
	void OnClicked_Stage1_3(USlowTextButton* InClickedButton);
	void OnClicked_Cancel(USlowTextButton* InClickedButton);

	void CloseWidget();
};

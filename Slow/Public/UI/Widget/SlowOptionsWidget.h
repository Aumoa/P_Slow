// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "UI/SlowWidgetBase.h"

#include "SlowOptionsWidget.generated.h"

class USlowTextButton;

UCLASS()
class SLOW_API USlowOptionsWidget : public USlowWidgetBase
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(USlowOptionsWidget, FDisposingEvent);

private:
	UPROPERTY(meta = (BindWidget))
	USlowTextButton* Button_Cancel;
	UPROPERTY(meta = (BindWidget))
	USlowTextButton* Button_Ok;

public:
	void NativeConstruct() override;

	FDisposingEvent Disposing;

private:
	void OnClicked_Ok(USlowTextButton* InClickedButton);
	void OnClicked_Cancel(USlowTextButton* InClickedButton);

	void CloseWidget();
};
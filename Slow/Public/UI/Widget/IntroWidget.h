// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlowWidgetBase.h"

#include "IntroWidget.generated.h"

class USlowTextButton;

UCLASS()
class SLOW_API UIntroWidget : public USlowWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	USlowTextButton* PlayButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	USlowTextButton* OptionButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	USlowTextButton* ExitButton;

public:
	void NativeConstruct() override;

private:
	void OnButtonClicked(USlowTextButton* InClickedButton);
};
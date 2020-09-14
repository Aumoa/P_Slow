// Copyright 2020 Team slow. All right reserved.

#include "UI/Widget/IntroWidget.h"

#include "UI/Control/SlowTextButton.h"
#include "UI/Widget/SlowOptionsWidget.h"
#include "UI/Widget/SlowStageSelectsWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/WidgetManager.h"
#include "Manager/SceneManager.h"
#include "Animation/WidgetAnimation.h"

void UIntroWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->Clicked.AddUObject(this, &UIntroWidget::OnButtonClicked);
	OptionButton->Clicked.AddUObject(this, &UIntroWidget::OnButtonClicked);
	ExitButton->Clicked.AddUObject(this, &UIntroWidget::OnButtonClicked);

	PlayAnimation(FadeIn);
}

void UIntroWidget::OnButtonClicked(USlowTextButton* InClickedButton)
{
	if (InClickedButton == PlayButton) {
		if (StageSelectsWidget == nullptr) {
			StageSelectsWidget = UWidgetManager::CreateSlowWidget<USlowStageSelectsWidget>(TEXT("Widget.SlowStageSelectsWidget"));
			StageSelectsWidget->Disposing.AddUObject(this, &UIntroWidget::OnDisposing_StageSelects);
		}
	}
	else if (InClickedButton == OptionButton) {
		if (OptionsWidget == nullptr) {
			OptionsWidget = UWidgetManager::CreateSlowWidget<USlowOptionsWidget>(TEXT("Widget.SlowOptionsWidget"));
			OptionsWidget->Disposing.AddUObject(this, &UIntroWidget::OnDisposing_Options);
		}
	}
	else if (InClickedButton == ExitButton) {
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
	}
}

void UIntroWidget::OnDisposing_Options()
{
	if (OptionsWidget != nullptr) {
		OptionsWidget->RemoveFromParent();
		OptionsWidget = nullptr;
	}
}

void UIntroWidget::OnDisposing_StageSelects()
{
	if (StageSelectsWidget != nullptr) {
		StageSelectsWidget->RemoveFromParent();
		StageSelectsWidget = nullptr;
	}
}
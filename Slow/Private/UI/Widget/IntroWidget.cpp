// Copyright 2020 Team slow. All right reserved.

#include "UI/Widget/IntroWidget.h"

#include "UI/Control/SlowTextButton.h"
#include "Kismet/KismetSystemLibrary.h"

void UIntroWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->Clicked.AddUObject(this, &UIntroWidget::OnButtonClicked);
	OptionButton->Clicked.AddUObject(this, &UIntroWidget::OnButtonClicked);
	ExitButton->Clicked.AddUObject(this, &UIntroWidget::OnButtonClicked);
}

void UIntroWidget::OnButtonClicked(USlowTextButton* InClickedButton)
{
	if (InClickedButton == PlayButton) {
		// Case on play.
	}
	else if (InClickedButton == OptionButton) {
		// Case on options.
	}
	else if (InClickedButton == ExitButton) {
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
	}
}
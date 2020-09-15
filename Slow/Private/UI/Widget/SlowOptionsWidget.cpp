// Copyright 2020 Team slow. All right reserved.

#include "UI/Widget/SlowOptionsWidget.h"
#include "UI/Control/SlowTextButton.h"

void USlowOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Cancel->Clicked.AddUObject(this, &USlowOptionsWidget::OnClicked_Cancel);
	Button_Ok->Clicked.AddUObject(this, &USlowOptionsWidget::OnClicked_Ok);
}

void USlowOptionsWidget::OnClicked_Ok(USlowTextButton* InClickedButton)
{
	Disposing.Broadcast();
}

void USlowOptionsWidget::OnClicked_Cancel(USlowTextButton* InClickedButton)
{
	Disposing.Broadcast();
}
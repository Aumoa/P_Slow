// Copyright 2020 Team slow. All right reserved.

#include "UI/Control/SlowTextButton.h"

#include "UI/Control/SlowText.h"
#include "Components/Button.h"
#include "Manager/WidgetManager.h"

void USlowTextButton::NativeConstruct()
{
	Super::NativeConstruct();

	MyButton->OnClicked.AddDynamic(this, &USlowTextButton::OnClicked);
}

void USlowTextButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	ButtonText->SetTextStyleBase(TextStyleBase);
	ButtonText->SetText(Text);
}

void USlowTextButton::SetText(const FText& InText)
{
	ButtonText->SetText(InText);
}

FText USlowTextButton::GetText() const
{
	return ButtonText->GetText();
}

FText USlowTextButton::GetRawText() const
{
	return ButtonText->GetRawText();
}

void USlowTextButton::SetTextStyleBase(const FSlowTextStyle& InStyleBase)
{
	ButtonText->SetTextStyleBase(InStyleBase);
}

FSlowTextStyle USlowTextButton::GetTextStyleBase() const
{
	return ButtonText->GetTextStyleBase();
}

void USlowTextButton::OnClicked()
{
	Clicked.Broadcast();
}
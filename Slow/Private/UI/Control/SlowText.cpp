// Copyright 2020 Team slow. All right reserved.

#include "UI/Control/SlowText.h"

#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

void USlowText::NativeConstruct()
{
	Super::NativeConstruct();
}

void USlowText::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// �����Ϳ��� �ؽ�Ʈ �Ǵ� ��Ÿ ������Ƽ�� ����� ��, ������Ƽ ������ �ݿ��մϴ�.
	SetText(Text);
}

void USlowText::SetText(const FText& text_)
{
	// ���� �ؽ�Ʈ ������ Ŭ�����մϴ�.
	Text = text_;
	ClearText();

	// RichText�� �Ľ��մϴ�.
	TArray<UTextBlock*> result;
	if (ParseString(&result)) {
		UHorizontalBox* newLine = AddNewLine();

		int32 count = result.Num();
		for (int32 i = 0; i < count; ++i) {
			if (result[i] != nullptr) {
				AppendingText(newLine, result[i]);
			}
			else {
				newLine = AddNewLine();
			}
		}
	}
	else {
		// �Ľ̿� �����Ͽ��� ���, ��ġ �ؽ�Ʈ�� �״�� ���÷��̿� ǥ���մϴ�.
		UHorizontalBox* newLine = AddNewLine();
		AppendingText(newLine, text_);
		DisplayText = text_;
	}
}

FText USlowText::GetText() const
{
	return DisplayText;
}

FText USlowText::GetRawText() const
{
	return Text;
}

void USlowText::ClearText()
{
	int32 count = TextAppendingBoxes.Num();

	for (int32 i = 0; i < count; ++i) {
		TextAppendingBoxes[i]->RemoveFromParent();
	}

	TextAppendingBoxes.Empty();
}

UHorizontalBox* USlowText::AddNewLine()
{
	const FString BoxName = TEXT("TextAppendingBox");

	UHorizontalBox* appendingBox = WidgetTree->ConstructWidget<UHorizontalBox>();
	TextAppendingBoxes.Add(appendingBox);
	TextWrappingBox->AddChild(appendingBox);

	return appendingBox;
}

void USlowText::AppendingText(UHorizontalBox* currentLine, const FText& text)
{
	UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>();
	textBlock->SetText(text);
	AppendingText(currentLine, textBlock);
}

void USlowText::AppendingText(UHorizontalBox* currentLine, UTextBlock* textBlock)
{
	currentLine->AddChild(textBlock);
}

bool USlowText::ParseString(TArray<UTextBlock*>* parsingResult)
{
	FString textString = Text.ToString();
	TUniquePtr<FStateMachine> state = FStateMachine::GetEntry(FStateMachine::FArguments(this, textString, 0), parsingResult);

	bool bSucceeded = true;
	while (state.Get() != nullptr && bSucceeded) {
		bSucceeded = state->ParseText();
		state = state->GetNextState();
	}

	return bSucceeded;
}
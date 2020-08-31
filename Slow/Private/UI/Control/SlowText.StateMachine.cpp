// Copyright 2020 Team slow. All right reserved.

#include "UI/Control/SlowText.h"

#include "Blueprint/WidgetTree.h"

USlowText::FStateMachine::FStyleDeltas::FStyleDeltas()
	: bBold(false)
	, bItalic(false)
	, TextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
{

}

USlowText::FStateMachine::FArguments::FArguments(USlowText* parent, const FString& reference, int32 seekpos)
	: Parent(parent)
	, StringReference(reference)
	, Seekpos(seekpos)
{

}

USlowText::FStateMachine::FArguments::FArguments(const FArguments& copy)
	: Parent(copy.Parent)
	, StringReference(copy.StringReference)
	, Seekpos(copy.Seekpos)
{

}

USlowText::FStateMachine::FStateMachine(const FArguments& args)
	: Args(args)
{

}

USlowText::FStateMachine::~FStateMachine()
{

}

auto USlowText::FStateMachine::GetNextState() const -> TUniquePtr<USlowText::FStateMachine>
{
	return MoveTemp(NextState);
}

USlowText* USlowText::FStateMachine::GetParent() const
{
	return Args.Parent.Get();
}

const FString& USlowText::FStateMachine::GetStringReference() const
{
	return Args.StringReference;
}

int32 USlowText::FStateMachine::GetSeekpos() const
{
	return Args.Seekpos;
}

void USlowText::FStateMachine::SetNext(TUniquePtr<FStateMachine>&& state)
{
	NextState = MoveTemp(state);
}

TUniquePtr<USlowText::FStateMachine> USlowText::FStateMachine::GetEntry(const FArguments& args, TArray<UTextBlock*>* outputResults)
{
	return MakeUnique<FDefaultStateMachine>(args, outputResults);
}

USlowText::FDefaultStateMachine::FDefaultStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults)
	: Super(args)
	, OutputResults(outputResults)
{
	CurrentDeltas.TextColor = GetParent()->TextStyleBase.ColorAndOpacity;
}

USlowText::FDefaultStateMachine::FDefaultStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults, const FStyleDeltas& currentDeltas)
	: Super(args)
	, OutputResults(outputResults)
	, CurrentDeltas(currentDeltas)
{

}

bool USlowText::FDefaultStateMachine::ParseText()
{
	const int32 Int32MaxValue = 0x7FFFFFFF;

	const FString& reference = GetStringReference();
	int32 seekpos = GetSeekpos();

	int32 newline = reference.Find(TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, seekpos);
	int32 findPos = reference.Find(TEXT("<"), ESearchCase::CaseSensitive, ESearchDir::FromStart, seekpos);

	if (findPos == -1) findPos = Int32MaxValue;
	if (newline == -1) newline = Int32MaxValue;

	bool bNewline = false;
	if (newline < findPos) {
		bNewline = true;
		findPos = newline;
	}

	int32 length = findPos == Int32MaxValue ? reference.Len() - seekpos : findPos - seekpos;

	if (length != 0) {
		if (bNewline && findPos != 0 && reference[findPos - 1] == L'\r') {
			length -= 1;
		}

		OutputResults->Add(MakeTextBlock(FText::FromString(reference.Mid(seekpos, length))));
	}

	if (bNewline) {
		OutputResults->Add(nullptr);
		SetNextInternal<FDefaultStateMachine>(findPos + 1);
	}
	else if (findPos != Int32MaxValue) {
		SetNextInternal<FOptionalStateMachine>(findPos);
	}

	return true;
}

UTextBlock* USlowText::FDefaultStateMachine::MakeTextBlock(const FText& substring) const
{
	USlowText* parent = GetParent();
	UTextBlock* textBlock = parent->WidgetTree->ConstructWidget<UTextBlock>();
	SetTextStyle(textBlock, parent->TextStyleBase);
	textBlock->SetText(substring);
	return textBlock;
}

void USlowText::FDefaultStateMachine::SetTextStyle(UTextBlock* this_, FSlowTextStyle style) const
{
	FString typeface = TEXT("Regular");

	if (CurrentDeltas.bBold) {
		typeface = TEXT("Bold");
	}

	if (CurrentDeltas.bItalic) {
		if (typeface == TEXT("Bold")) {
			typeface = TEXT("Bold Italic");
		}
		else {
			typeface = TEXT("Italic");
		}
	}

	style.Font.TypefaceFontName = *typeface;

	this_->SetColorAndOpacity(CurrentDeltas.TextColor);
	this_->SetFont(style.Font);
	this_->SetStrikeBrush(style.StrikeBrush);
	this_->SetShadowOffset(style.ShadowOffset);
	this_->SetShadowColorAndOpacity(style.ShadowColorAndOpacity);
}

template<class T>
void USlowText::FDefaultStateMachine::SetNextInternal(int32 findPos)
{
	SetNext(MakeUnique<T>(FArguments(GetParent(), GetStringReference(), findPos), OutputResults, CurrentDeltas));
}

USlowText::FOptionalStateMachine::FOptionalStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults, const FStyleDeltas& currentDeltas)
	: Super(args)
	, OutputResults(outputResults)
	, CurrentDeltas(currentDeltas)
{
	HandlersMap.Add(TEXT("b"), &FOptionalStateMachine::OnBoldKey);
	HandlersMap.Add(TEXT("i"), &FOptionalStateMachine::OnItalicKey);
	HandlersMap.Add(TEXT("color"), &FOptionalStateMachine::OnColorKey);
}

bool USlowText::FOptionalStateMachine::ParseText()
{
	const FString& reference = GetStringReference();
	int32 seekpos = GetSeekpos();

	int32 findPos = reference.Find(TEXT(">"), ESearchCase::CaseSensitive, ESearchDir::FromStart, seekpos);
	if (findPos == -1) {
		return false;
	}

	bool bSet = true;
	if (reference[seekpos + 1] == L'/') {
		bSet = false;
		seekpos += 1;
	}

	int32 length = findPos - seekpos;
	FString context = reference.Mid(seekpos + 1, length - 1).ToLower();

	FString key, value;
	int32 sep;

	if (context.FindChar(L'=', sep)) {
		key = context.Mid(0, sep);
		value = context.Mid(sep + 1, context.Len() - sep - 1);
	}
	else {
		key = context;
	}

	auto it = HandlersMap.Find(key);
	bool bSucceeded = true;

	if (it == nullptr) {
		return false;
	}
	else {
		bSucceeded = (this->*(*it))(CurrentDeltas, value, bSet);
		SetNext(MakeUnique<FDefaultStateMachine>(FArguments(GetParent(), GetStringReference(), findPos + 1), OutputResults, CurrentDeltas));
	}

	return bSucceeded;
}

bool USlowText::FOptionalStateMachine::OnBoldKey(FStyleDeltas& style, const FString& value, bool bSet)
{
	if (style.bBold == bSet) {
		return false;
	}

	style.bBold = bSet;
	return true;
}

bool USlowText::FOptionalStateMachine::OnItalicKey(FStyleDeltas& style, const FString& value, bool bSet)
{
	if (style.bItalic == bSet) {
		return false;
	}

	style.bItalic = bSet;
	return true;
}

bool USlowText::FOptionalStateMachine::OnColorKey(FStyleDeltas& style, const FString& value, bool bSet)
{
	if (bSet) {
		FColor color = FColor::FromHex(value);
		FLinearColor linearColor = color;
		FSlateColor slateColor = linearColor;

		style.TextColor = slateColor;
	}
	else {
		style.TextColor = GetParent()->TextStyleBase.ColorAndOpacity;
	}
	return true;
}
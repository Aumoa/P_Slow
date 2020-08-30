// Copyright 2020 Team slow. All right reserved.

#include "UI/Control/SlowText.h"

#include "Blueprint/WidgetTree.h"

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

class USlowText::FDefaultStateMachine : public FStateMachine
{
	using Super = FStateMachine;

	TArray<UTextBlock*>* OutputResults;
	TArray<FTextBlockStyle> StyleStack;

public:
	FDefaultStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults)
		: Super(args)
		, OutputResults(outputResults)
	{
		StyleStack.Push(args.Parent->TextStyleBase);
	}

	FDefaultStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults, TArray<FTextBlockStyle>&& styleStack)
		: Super(args)
		, OutputResults(outputResults)
		, StyleStack(MoveTemp(styleStack))
	{

	}

	bool ParseText() override
	{
		const FString& reference = GetStringReference();
		int32 seekpos = GetSeekpos();

		int32 findPos = reference.Find(TEXT("<"), ESearchCase::CaseSensitive, ESearchDir::FromStart, seekpos);
		if (findPos == -1) {
			OutputResults->Add(
				MakeTextBlock(FText::FromString(reference.Mid(seekpos, reference.Len() - seekpos)))
			);
		}
		else {
			return false;
		}

		return true;
	}

	TUniquePtr<FStateMachine> GetNextState(TUniquePtr<FStateMachine> this_) const override
	{
		return nullptr;
	}

private:
	UTextBlock* MakeTextBlock(const FText& substring) const
	{
		USlowText* parent = GetParent();
		UTextBlock* textBlock = parent->WidgetTree->ConstructWidget<UTextBlock>();
		textBlock->SetText(substring);
		return textBlock;
	}
};

USlowText::FStateMachine::FStateMachine(const FArguments& args)
	: Args(args)
{

}

USlowText::FStateMachine::~FStateMachine()
{

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

TUniquePtr<USlowText::FStateMachine> USlowText::FStateMachine::GetEntry(const FArguments& args, TArray<UTextBlock*>* outputResults)
{
	return MakeUnique<FDefaultStateMachine>(args, outputResults);
}
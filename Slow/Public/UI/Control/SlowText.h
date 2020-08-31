// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowControlBase.h"

#include "Structures/SlowTextStyle.h"

#include "SlowText.generated.h"

class UVerticalBox;
class UHorizontalBox;
class UTextBlock;

UCLASS()
class SLOW_API USlowText : public USlowControlBase
{
	GENERATED_BODY()

public:
	class FStateMachine;
	class FDefaultStateMachine;
	class FOptionalStateMachine;

private:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* TextWrappingBox;

	UPROPERTY(EditAnywhere, Category = Content, meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	FText Text;
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	FSlowTextStyle TextStyleBase;

	UPROPERTY()
	TArray<UHorizontalBox*> TextAppendingBoxes;
	FText DisplayText;

public:
	void NativeConstruct() override;
	void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable)
	void SetText(const FText& text_);
	UFUNCTION(BlueprintCallable)
	FText GetText() const;
	UFUNCTION(BlueprintCallable)
	FText GetRawText() const;

private:
	void ClearText();
	UHorizontalBox* AddNewLine();
	void AppendingText(UHorizontalBox* currentLine, const FText& text);
	void AppendingText(UHorizontalBox* currentLine, UTextBlock* textBlock);
	bool ParseString(TArray<UTextBlock*>* parsingResult);
};

class USlowText::FStateMachine
{
protected:
	struct FStyleDeltas
	{
		uint8 bBold : 1;
		uint8 bItalic : 1;
		FSlateColor TextColor;

		FStyleDeltas();
	};

public:
	struct FArguments
	{
		TWeakObjectPtr<USlowText> Parent;
		const FString& StringReference;
		int32 Seekpos;

		FArguments(USlowText* parent, const FString& reference, int32 seekpos);
		FArguments(const FArguments& copy);
	};

private:
	FArguments Args;
	mutable TUniquePtr<FStateMachine> NextState;  // Can movable.

public:
	FStateMachine(const FArguments& args);
	virtual ~FStateMachine();

	virtual bool ParseText() = 0;
	virtual TUniquePtr<FStateMachine> GetNextState() const;

	USlowText* GetParent() const;
	const FString& GetStringReference() const;
	int32 GetSeekpos() const;

	static TUniquePtr<FStateMachine> GetEntry(const FArguments& args, TArray<UTextBlock*>* outputResults);

protected:
	void SetNext(TUniquePtr<FStateMachine>&& state);
};

class USlowText::FDefaultStateMachine : public FStateMachine
{
	using Super = FStateMachine;

	TArray<UTextBlock*>* OutputResults;
	TUniquePtr<FStateMachine> NextState;
	FStyleDeltas CurrentDeltas;

public:
	FDefaultStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults);
	FDefaultStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults, const FStyleDeltas& currentDeltas);

	bool ParseText() override;

private:
	UTextBlock* MakeTextBlock(const FText& substring) const;
	void SetTextStyle(UTextBlock* this_, FSlowTextStyle style) const;
	template<class T>
	void SetNextInternal(int32 findPos);
};

class USlowText::FOptionalStateMachine : public FStateMachine
{
	using Super = FStateMachine;
	using Callback = bool (FOptionalStateMachine::*)(FStyleDeltas&, const FString&, bool);

	TArray<UTextBlock*>* OutputResults;
	FStyleDeltas CurrentDeltas;
	TMap<FString, Callback> HandlersMap;

public:
	FOptionalStateMachine(const FArguments& args, TArray<UTextBlock*>* outputResults, const FStyleDeltas& currentDeltas);

	bool ParseText() override;

private:
	bool OnBoldKey(FStyleDeltas& style, const FString& value, bool bSet);
	bool OnItalicKey(FStyleDeltas& style, const FString& value, bool bSet);
	bool OnColorKey(FStyleDeltas& style, const FString& value, bool bSet);
};
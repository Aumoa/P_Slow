// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlowWidgetBase.h"

#include "SlowText.generated.h"

class UVerticalBox;
class UHorizontalBox;
class UTextBlock;

UCLASS()
class SLOW_API USlowText : public USlowWidgetBase
{
	GENERATED_BODY()

private:
	class FStateMachine;
	class FDefaultStateMachine;

private:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* TextWrappingBox;

	UPROPERTY(EditAnywhere, Category = Content, meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	FText Text;
	UPROPERTY(EditAnywhere, Category = "TextBlock", meta = (AllowPrivateAccess = "true"))
	FTextBlockStyle TextStyleBase;

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
public:
	struct FArguments
	{
		TWeakObjectPtr<USlowText> Parent;
		const FString& StringReference;
		int32 Seekpos;

		FArguments(USlowText* parent, const FString& reference, int32 seekpos);
		FArguments(const FArguments& copy);
	};

	FArguments Args;

public:
	FStateMachine(const FArguments& args);
	virtual ~FStateMachine();

	virtual bool ParseText() = 0;
	virtual TUniquePtr<FStateMachine> GetNextState(TUniquePtr<FStateMachine> this_) const = 0;

	USlowText* GetParent() const;
	const FString& GetStringReference() const;
	int32 GetSeekpos() const;

	static TUniquePtr<FStateMachine> GetEntry(const FArguments& args, TArray<UTextBlock*>* outputResults);
};
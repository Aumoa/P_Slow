// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowControlBase.h"

#include "Structures/SlowTextStyle.h"

#include "SlowTextButton.generated.h"

class USlowText;
class UButton;

UCLASS()
class SLOW_API USlowTextButton : public USlowControlBase
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(USlowTextButton, FClickedEvent);

private:
	UPROPERTY(meta = (BindWidget))
	UButton* MyButton;
	UPROPERTY(meta = (BindWidget))
	USlowText* ButtonText;

	UPROPERTY(EditAnywhere, Category = Content, meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	FText Text;
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	FSlowTextStyle TextStyleBase;

public:
	void NativeConstruct() override;
	void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable)
	void SetText(const FText& InText);
	UFUNCTION(BlueprintPure)
	FText GetText() const;
	UFUNCTION(BlueprintPure)
	FText GetRawText() const;
	UFUNCTION(BlueprintCallable)
	void SetTextStyleBase(const FSlowTextStyle& InStyleBase);
	UFUNCTION(BlueprintPure)
	FSlowTextStyle GetTextStyleBase() const;

	FClickedEvent Clicked;

private:
	UFUNCTION()
	void OnClicked();
};
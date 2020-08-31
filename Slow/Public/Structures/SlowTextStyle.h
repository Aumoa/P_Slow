// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "SlowTextStyle.generated.h"

USTRUCT(BlueprintType)
struct SLOW_API FSlowTextStyle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateColor ColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush StrikeBrush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D ShadowOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor ShadowColorAndOpacity;
};
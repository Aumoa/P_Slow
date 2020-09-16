// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeConfig.generated.h"

USTRUCT(BlueprintType)
struct SLOW_API FBaseAttributeConfig
{
	GENERATED_BODY()

public:
	FBaseAttributeConfig();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimum")
	int64 MinHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maximum")
	int64 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start")
	int64 StartHealth;
};
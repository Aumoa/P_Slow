// Copyright 2020 Team slow. All right reserved.

#pragma once


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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimum")
	int64 MinStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maximum")
	int64 MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start")
	int64 StartStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Number")
	int64 StaminaIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Number")
	int64 DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName FriendlyName;

};
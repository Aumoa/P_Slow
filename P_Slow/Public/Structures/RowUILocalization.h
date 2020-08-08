// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "RowUILocalization.generated.h"

USTRUCT(BlueprintType)
struct FRowUILocalization : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text")
	FText Localized_Ko;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text")
	FText Localized_En;
};
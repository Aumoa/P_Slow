// Copyright 2020 Aumoa.lib. All right reserved.

#pragma once

#include "SublevelGroup.generated.h"

USTRUCT(BlueprintType)
struct SLOW_API FSublevelGroup : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FString> SublevelsName;
};
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "Index2D.generated.h"

USTRUCT(BlueprintType)
struct SLOW_API FIndex2D
{
	GENERATED_BODY()

public:
	FIndex2D();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;
};
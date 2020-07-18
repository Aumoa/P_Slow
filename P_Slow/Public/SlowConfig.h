// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SlowConfig.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class P_SLOW_API USlowConfig : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString EntryPoint;
	UPROPERTY( EditAnywhere, BlueprintReadWrite ) bool bSkipDemo;
};

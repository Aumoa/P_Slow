// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "UI/SlowWidgetBase.h"

#include "SlowControlBase.generated.h"

UCLASS(BlueprintType)
class SLOW_API USlowControlBase : public USlowWidgetBase
{
	GENERATED_BODY()

private:

public:
	void NativeConstruct() override;
};
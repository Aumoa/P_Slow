// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SlowWidgetBase.generated.h"

UCLASS()
class SLOW_API USlowWidgetBase : public UUserWidget
{
	GENERATED_BODY()

	friend class UWidgetManager;

public:
	DECLARE_EVENT(USlowWidgetBase, PendingCloseEvent);

private:
	uint8 bPendingClose : 1;

public:
	USlowWidgetBase();

	void RemoveFromParent() override;

	UFUNCTION(BlueprintCallable)
	void MakeWidgetPendingClose();

	UFUNCTION(BlueprintPure)
	bool IsPendingClose();

	PendingCloseEvent PendingClose;
};
// Copyright 2020 Team slow. All right reserved.

#include "UI/SlowWidgetBase.h"

USlowWidgetBase::USlowWidgetBase() : Super(FObjectInitializer::Get())
{
	bPendingClose = false;
}

void USlowWidgetBase::RemoveFromParent()
{
	if (!bPendingClose)
	{
		MakeWidgetPendingClose();
	}
}

void USlowWidgetBase::MakeWidgetPendingClose()
{
	bPendingClose = true;
	PendingClose.Broadcast();

	Super::RemoveFromParent();
}

bool USlowWidgetBase::IsPendingClose()
{
	return bPendingClose;
}
// Copyright 2020 Team slow. All right reserved.

#include "Component/Behavior.h"

UBehavior::UBehavior()
{
	ActivateStateStack.Push(true);
}

void UBehavior::SetActivate(bool bInActivate)
{
	ActivateStateStack.SetNum(1, false);
	ActivateStateStack[0] = bInActivate;
}

bool UBehavior::IsActivated() const
{
	return ActivateStateStack.Top();
}

void UBehavior::PushActivate(bool bInActivate)
{
	ActivateStateStack.Push(bInActivate);
}

void UBehavior::PopActivate()
{
	if (ActivateStateStack.Num() > 1) {
		ActivateStateStack.Pop();
	}
}
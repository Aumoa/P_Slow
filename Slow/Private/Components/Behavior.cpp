// Copyright 2020 Team slow. All right reserved.

#include "Components/Behavior.h"
#include "Effect/StatModifyLinearEffect.h"
#include "Effect/ActorEffect.h"


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

void UBehavior::RemoveFromParent()
{
	FString componentName = GetClass()->GetFName().ToString();

	AActor* owner = GetOwner();
	if (owner == nullptr) {
		return;
	}

	DestroyComponent(false);

	//UE_LOG(LogSlow, Log, TEXT("UBehavior::RemoveFromParent(): Component %s is removed."), *componentName);
}

void UBehavior::AddEffect(FActorEffect* InEffect)
{
	EffectList.Add(InEffect);
}
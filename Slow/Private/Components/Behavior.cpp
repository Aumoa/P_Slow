// Copyright 2020 Team slow. All right reserved.

#include "Components/Behavior.h"
#include "Effect/StatModifyLinearEffect.h"
#include "Effect/ActorEffect.h"


UBehavior::UBehavior()
{
	ActivateStateStack.Push(false);
	ActivateStateStack.Push(true);
	PrimaryComponentTick.bCanEverTick = true;
}

void UBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsActivated() == false)
	{
		RemoveFromParent();
		return;
	}

	if (GetOwner() == nullptr)
	{

		return;
	}

	for (FActorEffect* Effect : EffectList)
	{
		Effect->Apply(this->GetOwner());
	}

	PopActivate();
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

void UBehavior::AddEffectList(TArray<FActorEffect*> InEffectList)
{
	EffectList.Append(InEffectList);
}

void UBehavior::SetEffect(TArray<FActorEffect*> InEffectList)
{
	EffectList.Empty();
	EffectList = InEffectList;
}

int UBehavior::GetEffectCount()
{
	return EffectList.Num();
}
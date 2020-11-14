// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "Behavior.generated.h"

class FStatModifyLinearEffect;
class FActorEffect;

UCLASS()
class SLOW_API UBehavior : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<bool> ActivateStateStack;
	TArray<FActorEffect *> EffectList;

public:
	UBehavior();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetActivate(bool bInActivate);
	bool IsActivated() const;

	void PushActivate(bool bInActivate);
	void PopActivate();

	void RemoveFromParent();
	void AddEffect(FActorEffect* InEffect);
};
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Behavior.generated.h"

UCLASS()
class SLOW_API UBehavior : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<bool> ActivateStateStack;

public:
	UBehavior();

	void SetActivate(bool bInActivate);
	bool IsActivated() const;

	void PushActivate(bool bInActivate);
	void PopActivate();
};
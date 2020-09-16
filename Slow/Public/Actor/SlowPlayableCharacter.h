// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlowStatBasedCharacter.h"

#include "SlowPlayableCharacter.generated.h"

UCLASS()
class SLOW_API ASlowPlayableCharacter : public ASlowStatBasedCharacter
{
	GENERATED_BODY()

public:
	ASlowPlayableCharacter();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
	void OnActionInput(const FName& ActionName, bool bPressed);

private:
	void OnMouseAction(bool bPressed);
};

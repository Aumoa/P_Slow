// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "SlowCharacter.generated.h"

UCLASS()
class P_SLOW_API ASlowCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void OnActionInput( const FName& ActionName, bool bPressed );
};

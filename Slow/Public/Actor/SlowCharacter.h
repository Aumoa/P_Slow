// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Attributes/CombatTag.h"

#include "SlowCharacter.generated.h"

UCLASS()
class SLOW_API ASlowCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCombatTag CombatTag;

public:
	ASlowCharacter();

	void SetCombatTag(const FCombatTag& InCombatTag);
	FCombatTag GetCombatTag() const;
};

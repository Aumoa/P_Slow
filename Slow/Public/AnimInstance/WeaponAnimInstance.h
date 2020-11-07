// Copyright 2020. Team slow, All right reserved.

#pragma once



#include "WeaponAnimInstance.generated.h"

class ASlowPlayableCharacter;
class UWeaponManager;

UCLASS()
class SLOW_API UWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<ASlowPlayableCharacter> SlowPC;

public:
	

};
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SlowConfig.generated.h"

class UWeaponBase;

UCLASS( Blueprintable )
class SLOW_API USlowConfig : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General", meta = (AllowPrivateAccess = "true"))
	uint8 bSkipDemo : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <UWeaponBase> HatchetWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <UWeaponBase> SwordWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <UWeaponBase> HammerWeapon;

public:
	USlowConfig(const FObjectInitializer& Initializer);

	bool IsSkipDemo() const;
	TSubclassOf<UWeaponBase> GetHatchetWeaponClass() const;
	TSubclassOf<UWeaponBase> GetSwordWeaponClass() const;
	TSubclassOf<UWeaponBase> GetHammerWeaponClass() const;
};

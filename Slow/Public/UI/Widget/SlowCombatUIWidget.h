// Copyright 2020. Team slow, All right reserved.
#pragma once


#include "UI/SlowWidgetBase.h"

#include "SlowCombatUIWidget.generated.h"

class USlowTextButton;
class USceneBase;
class ASlowStatBasedCharacter;
class ASlowPlayableCharacter;

UCLASS()
class SLOW_API USlowCombatUIWidget : public USlowWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASlowPlayableCharacter* OwnerCharacter;

	UPROPERTY()
	ASlowStatBasedCharacter* MyTarget;

public:
	//DECLARE_EVENT(USlowCombatUIWidget, FDisposingEvent);

	UFUNCTION(BlueprintCallable)
	float GetBossHP_Percent();

	UFUNCTION(BlueprintCallable)
	FName GetBossName();

	UFUNCTION(BlueprintCallable)
	float GetPlayerHP_Percent();

	UFUNCTION(BlueprintCallable)
	float GetPlayerStamina_Percent();

	UFUNCTION(BlueprintCallable)
	int GetCurrentWeapon();

	void SetTarget(ASlowStatBasedCharacter *Target);

	void SetOwnerCharacter(ASlowPlayableCharacter* Character);
};
// Copyright 2020 Team slow. All right reserved.

#include "UI/Widget/SlowCombatUIWidget.h"
#include "Actor/SlowStatBasedCharacter.h"


float USlowCombatUIWidget::GetBossHP_Percent()
{
	if (MyTarget == nullptr)
	{
		

		return 0.0f;
	}

	float result = MyTarget->GetCurrentHP() / MyTarget->GetMaxHP();


	return result;
}

FName USlowCombatUIWidget::GetBossName()
{
	if (MyTarget == nullptr)
	{
		return TEXT(" ");
	}

	if (GetBossHP_Percent() <= 0.0f)
	{
		return TEXT(" ");
	}
	
	return MyTarget->GetInitialAttribute().FriendlyName;
}

float USlowCombatUIWidget::GetPlayerHP_Percent()
{
	if (OwnerCharacter == nullptr)
	{
		return 0.0f;
	}

	float result = OwnerCharacter->GetCurrentHP() / OwnerCharacter->GetMaxHP();

	return result;
}

float USlowCombatUIWidget::GetPlayerStamina_Percent()
{
	if (OwnerCharacter == nullptr)
	{
		return 0.0f;
	}

	float result = OwnerCharacter->GetCurrentAttributes().StaminaPoint / OwnerCharacter->GetInitialAttribute().MaxStamina;

	return result;
}

int USlowCombatUIWidget::GetCurrentWeapon()
{
	if (OwnerCharacter == nullptr)
	{
		return -1;
	}

	return OwnerCharacter->GetCurrentWeaponNum();
}

void USlowCombatUIWidget::SetTarget(ASlowStatBasedCharacter* Target)
{
	MyTarget = Target;
}

void USlowCombatUIWidget::SetOwnerCharacter(ASlowPlayableCharacter* Character)
{
	OwnerCharacter = Character;
}

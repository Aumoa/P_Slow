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

float USlowCombatUIWidget::GetPlayerHP_Percent()
{
	if (OwnerCharacter == nullptr)
	{
		return 0.0f;
	}

	float result = OwnerCharacter->GetCurrentHP() / OwnerCharacter->GetMaxHP();

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

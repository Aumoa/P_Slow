// Copyright 2020. Team slow, All right reserved.


#include "Components/StatAttribute.h"

#include "LogDefine.h"

UStatAttribute::UStatAttribute()
{
	PrimaryComponentTick.bCanEverTick = false;
	bBeginMaxCurrent = true;
}

void UStatAttribute::BeginPlay()
{
	if ( bBeginMaxCurrent )
	{
		CurrentHealth = MaxHealth;
	}
}

void UStatAttribute::ApplyDamage( const FDamage& Damage )
{
	ApplyFixedDamage( Damage );
}

void UStatAttribute::ApplyFixedDamage( const FDamage& Damage )
{
	if ( CurrentHealth < Damage.FixedHealth )
	{
		CurrentHealth = 0;
		HealthKilled.Broadcast( this );
	}
}
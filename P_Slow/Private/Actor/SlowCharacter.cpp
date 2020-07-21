// Copyright 2020. Team slow, All right reserved.


#include "Actor/SlowCharacter.h"

#include "Components/StatAttribute.h"

ASlowCharacter::ASlowCharacter()
{
	Stats = CreateDefaultSubobject<UStatAttribute>( TEXT( "Stats" ) );
	AddOwnedComponent( Stats );
}

void ASlowCharacter::OnActionInput( const FName& ActionName, bool bPressed )
{

}
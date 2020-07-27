// Copyright 2020. Team slow, All right reserved.


#include "Actor/SlowCharacter.h"

#include "Components/StatComponent.h"

ASlowCharacter::ASlowCharacter()
{
	auto StatComponent = CreateDefaultSubobject<UStatComponent>( TEXT( "StatComponent" ) );
	AddOwnedComponent( StatComponent );
}

void ASlowCharacter::OnActionInput( const FName& ActionName, bool bPressed )
{

}
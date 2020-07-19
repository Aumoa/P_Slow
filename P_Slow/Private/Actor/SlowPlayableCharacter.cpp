// Copyright 2020. Team slow, All right reserved.

#include "Actor/SlowPlayableCharacter.h"

#include "GameFramework/PlayerController.h"

#include "Components/InputComponent.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "SlowTraceChannels.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"

ASlowPlayableCharacter::ASlowPlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bCanMove = true;
}

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowPlayableCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASlowPlayableCharacter::OnActionInput( const FName& ActionName, bool bPressed )
{
	if ( ActionName == IA_MouseAction )
	{
		OnMouseAction( bPressed );
	}
}

void ASlowPlayableCharacter::OnMouseAction( bool bPressed )
{
	if ( bPressed )
	{
		auto PlayerController = Cast<APlayerController>( Controller );

		FHitResult HitResult;
		bool bHit = PlayerController->GetHitResultAtScreenPosition( GetCurrentMouseScreenPos( PlayerController ), ECC_AcceptMouseAction, false, HitResult );

		if ( bHit )
		{
			UE_LOG( LogSlow, Log, TEXT( "ASlowPlayableCharacter::OnMouseAction(), HitResultX: %f, HitResultY: %f" ), HitResult.Location.X, HitResult.Location.Y );
			UAIBlueprintHelperLibrary::SimpleMoveToLocation( PlayerController, HitResult.Location );
		}
	}
}

FVector2D ASlowPlayableCharacter::GetCurrentMouseScreenPos( APlayerController* PlayerController ) const
{
	float MouseX;
	float MouseY;
	PlayerController->GetMousePosition( MouseX, MouseY );

	UE_LOG( LogSlow, Log, TEXT( "ASlowPlayableCharacter::GetCurrentMouseScreenPos(), MouseX: %f, MouseY: %f" ), MouseX, MouseY );

	return FVector2D( MouseX, MouseY );
}
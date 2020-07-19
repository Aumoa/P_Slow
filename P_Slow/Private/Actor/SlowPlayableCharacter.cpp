// Copyright 2020. Team slow, All right reserved.

#include "Actor/SlowPlayableCharacter.h"

ASlowPlayableCharacter::ASlowPlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowPlayableCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASlowPlayableCharacter::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}
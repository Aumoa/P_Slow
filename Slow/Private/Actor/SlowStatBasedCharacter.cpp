// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowStatBasedCharacter.h"

#include "LogDefine.h"

void ASlowStatBasedCharacter::BeginPlay()
{
	Super::BeginPlay();

	bBeginPlay = true;
}

ASlowStatBasedCharacter::ASlowStatBasedCharacter()
{
	bBeginPlay = false;
}

void ASlowStatBasedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlowStatBasedCharacter::SetInitialAttribute(const FBaseAttributeConfig& InInitialAttribute)
{
	if (!bBeginPlay) {
		InitialAttribute = InInitialAttribute;
	}
	else {
		UE_LOG(LogSlow, Error, TEXT("ASlowStatBasedCharacter::SetInitialAttribute(): This function can invoke only before begin play."));
	}
}
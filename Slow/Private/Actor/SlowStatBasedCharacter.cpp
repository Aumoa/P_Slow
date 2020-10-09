// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowStatBasedCharacter.h"

#include "LogDefine.h"
#include "Components/Behavior.h"

void ASlowStatBasedCharacter::BeginPlay()
{
	Super::BeginPlay();
}

ASlowStatBasedCharacter::ASlowStatBasedCharacter()
{

}

void ASlowStatBasedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FEquipments ASlowStatBasedCharacter::GetCurrentEquipments() const
{
	return FEquipments();
}

void ASlowStatBasedCharacter::SetInitialAttribute(const FBaseAttributeConfig& InInitialAttribute)
{
	if (!HasActorBegunPlay()) {
		InitialAttribute = InInitialAttribute;
	}
	else {
		UE_LOG(LogSlow, Error, TEXT("ASlowStatBasedCharacter::SetInitialAttribute(): This function can invoke only before begin play."));
	}
}
// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowPlayableCharacter.h"

#include "SlowTraceChannels.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Components/StatComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ASlowPlayableCharacter::ASlowPlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	AddOwnedComponent(StatComponent);
}

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlowPlayableCharacter::OnActionInput(const FName& ActionName, bool bPressed)
{
	if (ActionName == IA_MouseAction)
	{
		OnMouseAction(bPressed);
	}
}

void ASlowPlayableCharacter::OnMouseAction(bool bPressed)
{
	if (bPressed)
	{
		auto PlayerController = Cast<APlayerController>(Controller);

		FHitResult HitResult;
		bool bHit = PlayerController->GetHitResultUnderCursor(ECC_AcceptMouseAction, false, HitResult);

		if (bHit)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, HitResult.Location);
		}
	}
}
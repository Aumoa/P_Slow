// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowPlayableCharacter.h"

#include "SlowTraceChannels.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Ability/AbilityBase.h"
#include "Ability/MoveAbility.h"
#include "Ability/ILocationTargetAbility.h"
#include "Manager/WeaponManager.h"

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveAbility = MakeShared<FMoveAbility>();

	MouseActionSlot.SetAbility(MoveAbility.Get());
}

ASlowPlayableCharacter::ASlowPlayableCharacter()
{

}

ASlowPlayableCharacter::~ASlowPlayableCharacter()
{

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

	if (ActionName == IA_WeaponSwap)
	{
		UWeaponManager::NextWeapon();
	}
}

void ASlowPlayableCharacter::OnMouseAction(bool bPressed)
{
	if (bPressed)
	{
		auto PlayerController = Cast<APlayerController>(Controller);

		FHitResult HitResult;
		bool bHit = PlayerController->GetHitResultUnderCursor(ECC_AcceptMouseAction, false, HitResult);

		if (bHit) {
			TSharedPtr<FAbilityBase> ability = MouseActionSlot.GetAbility().Pin();
			if (!ability.IsValid()) {
				return;
			}

			auto targetBasedAbility = dynamic_cast<ILocationTargetAbility*>(ability.Get());
			if (targetBasedAbility == nullptr) {
				return;
			}

			targetBasedAbility->ExecuteIndirect(this);
			targetBasedAbility->SetTarget(HitResult.Location);
		}
	}
}

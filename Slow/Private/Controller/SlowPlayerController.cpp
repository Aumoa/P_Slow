// Copyright 2020 Team slow. All right reserved.

#include "Controller/SlowPlayerController.h"

#include "SlowGameInstance.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"
#include "Manager/SceneManager.h"
#include "Manager/InputManager.h"
#include "Components/InputComponent.h"
#include "Scene/SceneBase.h"
#include "Actor/SlowPlayableCharacter.h"

ASlowPlayerController::ASlowPlayerController()
{
	bShowMouseCursor = true;
}

void ASlowPlayerController::BeginPlay()
{
	Super::BeginPlay();

	USceneManager::BeginLevel(this);
	UInputManager::SetPlayerController(this);
}

void ASlowPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(IA_MouseAction, IE_Pressed, this, &ASlowPlayerController::OnMouseActionPressed);
	InputComponent->BindAction(IA_WeaponSwap, IE_Pressed, this, &ASlowPlayerController::OnWeaponSwapButtonPressed);
	InputComponent->BindAction(IA_Interaction, IE_Pressed, this, &ASlowPlayerController::OnInteractionButtonPressed);
	InputComponent->BindAction(IA_Roll, IE_Pressed, this, &ASlowPlayerController::OnRollButtonPressed);

}

void ASlowPlayerController::OnPossess(APawn* Target)
{
	Super::OnPossess(Target);

	Possessed = Cast<ASlowPlayableCharacter>(Target);
}

void ASlowPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	Possessed = nullptr;
}

void ASlowPlayerController::OnMouseActionPressed()
{
	if (Possessed != nullptr) {
		Possessed->OnActionInput(IA_MouseAction, true);
	}
}

void ASlowPlayerController::OnWeaponSwapButtonPressed()
{
	if (Possessed != nullptr)
	{
		Possessed->OnActionInput(IA_WeaponSwap, true);
	}
}

void ASlowPlayerController::OnInteractionButtonPressed()
{
	if (Possessed != nullptr)
	{
		Possessed->OnActionInput(IA_Interaction,true);
	}
}

void ASlowPlayerController::OnRollButtonPressed()
{
	if (Possessed != nullptr)
	{
		Possessed->OnActionInput(IA_Roll, true);
	}
}

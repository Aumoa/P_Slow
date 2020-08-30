// Copyright 2020 Team slow. All right reserved.

#include "Controller/SlowPlayerController.h"

#include "SlowGameInstance.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"
#include "Manager/SceneManager.h"
#include "Manager/InputManager.h"
#include "Components/InputComponent.h"
#include "Scene/SceneBase.h"
#include "Actor/SlowCharacter.h"

ASlowPlayerController::ASlowPlayerController()
{
	bShowMouseCursor = true;
}

void ASlowPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UInputManager::SetPlayerController(this);
}

void ASlowPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(IA_IntroNextSceneInput, IE_Pressed, this, &ASlowPlayerController::OnIntroNextSceneInputPressed);
	InputComponent->BindAction(IA_MouseAction, IE_Pressed, this, &ASlowPlayerController::OnMouseActionPressed);
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

void ASlowPlayerController::OnIntroNextSceneInputPressed()
{
	USceneManager::SendInputAction(IA_IntroNextSceneInput, true);
}

void ASlowPlayerController::OnMouseActionPressed()
{
	if (Possessed != nullptr) {
		Possessed->OnActionInput(IA_MouseAction, true);
	}
}
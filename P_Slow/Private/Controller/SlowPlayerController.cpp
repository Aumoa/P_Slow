// Copyright 2020. Team slow, All right reserved.


#include "Controller/SlowPlayerController.h"

#include "SlowGameInstance.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"

#include "Manager/SceneManager.h"

#include "Components/InputComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Scene/SceneBase.h"

#include "Actor/SlowCharacter.h"

ASlowPlayerController::ASlowPlayerController()
{
	bShowMouseCursor = true;
}

void ASlowPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( this ) );
}

void ASlowPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction( IA_IntroNextSceneInput, IE_Pressed, this, &ASlowPlayerController::OnIntroNextSceneInputPressed );
	InputComponent->BindAction( IA_MouseAction, IE_Pressed, this, &ASlowPlayerController::OnMouseActionPressed );
}

void ASlowPlayerController::OnPossess( APawn* Target )
{
	Super::OnPossess( Target );

	Possessed = Cast<ASlowCharacter>( Target );
}

void ASlowPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	Possessed = nullptr;
}

void ASlowPlayerController::OnIntroNextSceneInputPressed()
{
	USceneManager::SendInputAction( this, IA_IntroNextSceneInput, true );
}

void ASlowPlayerController::OnMouseActionPressed()
{
	if ( Possessed )
	{
		Possessed->OnActionInput( IA_MouseAction, true );
	}
}
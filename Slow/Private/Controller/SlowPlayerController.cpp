// Copyright 2020 Team slow. All right reserved.

#include "Controller/SlowPlayerController.h"

#include "SlowGameInstance.h"
#include "Common/SlowInputDefine.h"
#include "Manager/SceneManager.h"
#include "Manager/InputManager.h"
#include "Scene/SceneBase.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Common/SlowCommonMacros.h"

ASlowPlayerController::FGameThreadActionDelegateArgs::FGameThreadActionDelegateArgs(UObject* InSender, UObject* InArgs, float InDelay)
{
	this->Sender = InSender;
	this->Args = InArgs;
	this->DelayedInvoke = InDelay;
}

void ASlowPlayerController::FGameThreadActionDelegateArgs::ResolveInGameThread()
{
	if (!Sender.IsValid())
	{
		Sender = nullptr;
	}

	if (!Args.IsValid())
	{
		Args = nullptr;
	}
}

ASlowPlayerController::ASlowPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASlowPlayerController::BeginPlay()
{
	GameThreadCS = MakeUnique<FCriticalSection>();

	Super::BeginPlay();

	USceneManager::BeginLevel(this);
	UInputManager::SetPlayerController(this);
}

void ASlowPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(IA_MouseAction, IE_Pressed, this, &ASlowPlayerController::OnMouseActionPressed);

	InputComponent->BindAction(IA_MouseSelection,IE_Pressed, this, &ASlowPlayerController::OnMouseSelectionPressed);
	InputComponent->BindAction(IA_MouseSelection,IE_Released, this, &ASlowPlayerController::OnMouseSelectionReleased);


	InputComponent->BindAction(IA_WeaponSwap, IE_Pressed, this, &ASlowPlayerController::OnWeaponSwapButtonPressed);
	InputComponent->BindAction(IA_Interaction, IE_Pressed, this, &ASlowPlayerController::OnInteractionButtonPressed);
	InputComponent->BindAction(IA_Roll, IE_Pressed, this, &ASlowPlayerController::OnRollButtonPressed);
	InputComponent->BindAction(IA_Cursor, IE_Pressed, this, &ASlowPlayerController::OnCursorActionPressed);
	InputComponent->BindAction(IA_Jump, IE_Pressed, this, &ASlowPlayerController::OnJumpButtonPressed);
	InputComponent->BindAction(IA_PeaceMode, IE_Pressed, this, &ASlowPlayerController::OnPeaceModePressed);
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

void ASlowPlayerController::Tick(float InDeltaSeconds)
{
	TArray<FGameThreadActionPair> ExecuteQueue;
	{
		ScopedLock(GameThreadCS);
		
		for (int32 i = 0; i < GameThreadActionQueue.Num(); ++i)
		{
			auto& Item = GameThreadActionQueue[i];
			auto& [Func, Args] = GameThreadActionQueue[i];

			Args.DelayedInvoke -= InDeltaSeconds;
			
			if (Args.DelayedInvoke <= 0.0f)
			{
				Args.DelayedInvoke = 0;
				ExecuteQueue.Add(Item);

				GameThreadActionQueue.RemoveAtSwap(i);
				i -= 1;
			}
		}
	}

	for (auto& Item : ExecuteQueue)
	{
		auto&& Func = MoveTemp(Item.Key);
		auto&& Args = MoveTemp(Item.Value);

		Args.ResolveInGameThread();
		Func(Args.Sender.Get(), Args.Args.Get());
	}
}

void ASlowPlayerController::EnqueueGameThreadAction(FGameThreadActionDelegate CallbackProc, const FGameThreadActionDelegateArgs& InArgs)
{
	ScopedLock(GameThreadCS);
	GameThreadActionQueue.Emplace(CallbackProc, InArgs);
}

void ASlowPlayerController::OnMouseActionPressed()
{
	if (Possessed != nullptr) {
		Possessed->OnActionInput(IA_MouseAction, true);
	}
}

void ASlowPlayerController::OnMouseSelectionPressed()
{
	if (Possessed != nullptr) {
		Possessed->OnActionInput(IA_MouseSelection, true);
	}
}

void ASlowPlayerController::OnMouseSelectionReleased()
{
	
	if (Possessed != nullptr) {
		Possessed->OnActionInput(IA_MouseSelection, false);
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

void ASlowPlayerController::OnCursorActionPressed()
{
	bShowMouseCursor = CursorUsable = CursorUsable ? false : true;
}

void ASlowPlayerController::OnJumpButtonPressed()
{
	if (Possessed != nullptr) 
	{
		Possessed->OnActionInput(IA_Jump, true);
	}
}

void ASlowPlayerController::OnPeaceModePressed()
{
	if (Possessed != nullptr)
	{
		Possessed->OnActionInput(IA_PeaceMode, true);
	}
}
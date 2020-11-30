// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "SlowPlayerController.generated.h"

class USlowGameInstance;
class UInputComponent;
class ASlowPlayableCharacter;

UCLASS()
class SLOW_API ASlowPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	struct FGameThreadActionDelegateArgs
	{
		// 개체는 반드시 게임 스레드에서 레퍼런스 카운팅이 이루어져야 합니다.
		TWeakObjectPtr<UObject> Sender;
		TWeakObjectPtr<UObject> Args;
		float DelayedInvoke;

		FGameThreadActionDelegateArgs(UObject* InSender = nullptr, UObject* InArgs = nullptr, float InDelay = 0);

		void ResolveInGameThread();
	};

	using FGameThreadActionDelegate = TFunction<void(UObject* InSender, UObject* InArgs)>;
	using FGameThreadActionPair = TPair<FGameThreadActionDelegate, FGameThreadActionDelegateArgs>;

private:
	UPROPERTY()
	ASlowPlayableCharacter* Possessed;
	bool CursorUsable;

	TUniquePtr<FCriticalSection> GameThreadCS;
	TArray<FGameThreadActionPair> GameThreadActionQueue;

public:
	ASlowPlayerController();
	
public:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void OnPossess(APawn* Target) override;
	void OnUnPossess() override;
	void Tick(float InDeltaSeconds) override;

	void EnqueueGameThreadAction(FGameThreadActionDelegate CallbackProc, const FGameThreadActionDelegateArgs& InArgs = FGameThreadActionDelegateArgs());

private:
	void OnMouseActionPressed();
	void OnMouseSelectionPressed();
	void OnMouseSelectionReleased();
	void OnWeaponSwapButtonPressed();
	void OnInteractionButtonPressed();
	void OnRollButtonPressed();
	void OnCursorActionPressed();
	void OnJumpButtonPressed();
	void OnPeaceModePressed();
};
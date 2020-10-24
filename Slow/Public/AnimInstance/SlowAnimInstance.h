// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Misc/SlowVariant.h"
#include "Misc/TriggerBool.h"

#include "SlowAnimInstance.generated.h"

class ASlowPlayableCharacter;
class UCharacterMovementComponent;

UCLASS()
class SLOW_API USlowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	using FMyVariant = TSlowVariant<int, float, bool, FTriggerBool>;

private:
	TMap<FName, FMyVariant> VariantMap;

	mutable TWeakObjectPtr<ASlowPlayableCharacter> SlowPC;
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;
	static bool ManagerAccessibleState;

public:
	USlowAnimInstance();

	void NativeUpdateAnimation(float InDeltaSeconds) override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetFloat(FName VarName, float Value);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetInt(FName VarName, int Value);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetBool(FName VarName, bool Value);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetTrigger(FName VarName);

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetFloat(FName VarName) const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	int GetInt(FName VarName) const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetBool(FName VarName) const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetTriggerBool(FName VarName) const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	int GetCurrentWeaponNum() const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetSwapAnimState() const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetIsFindInteractionObject() const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetRollAnimState() const;

	static void SetManagerAccessibleState(const bool Accessstate);
	static bool GetManagerAccessibleState();

	bool TrySetSlowPC(ASlowPlayableCharacter *pc) const;

private:
	template<class T>
	void SetValueInternal(FName VarName, T Value);

	template<class T>
	T GetValueInternal(FName VarName) const;
	
};
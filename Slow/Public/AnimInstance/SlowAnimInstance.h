// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Misc/Variant.h"

#include "SlowAnimInstance.generated.h"

class ASlowPlayableCharacter;
class UCharacterMovementComponent;

UCLASS()
class SLOW_API USlowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	using FMyVariant = TVariant<int, float, bool>;

private:
	TMap<FName, FMyVariant> VariantMap;

	TWeakObjectPtr<ASlowPlayableCharacter> SlowPC;
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

public:
	USlowAnimInstance();

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetFloat(FName VarName, float Value);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetInt(FName VarName, int Value);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetBool(FName VarName, bool Value);

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetFloat(FName VarName) const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	int GetInt(FName VarName) const;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetBool(FName VarName) const;

private:
	template<class T>
	void SetValueInternal(FName VarName, T Value);

	template<class T>
	T GetValueInternal(FName VarName) const;
};
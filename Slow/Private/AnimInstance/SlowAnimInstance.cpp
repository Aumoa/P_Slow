// Copyright 2020 Team slow. All right reserved.

#include "AnimInstance/SlowAnimInstance.h"

#include "Actor/SlowPlayableCharacter.h"

USlowAnimInstance::USlowAnimInstance()
{

}

void USlowAnimInstance::SetFloat(FName VarName, float Value)
{
	SetValueInternal<float>(VarName, Value);
}

void USlowAnimInstance::SetInt(FName VarName, int Value)
{
	SetValueInternal<int>(VarName, Value);
}

void USlowAnimInstance::SetBool(FName VarName, bool Value)
{
	SetValueInternal<bool>(VarName, Value);
}

float USlowAnimInstance::GetFloat(FName VarName) const
{
	return GetValueInternal<float>(VarName);
}

int USlowAnimInstance::GetInt(FName VarName) const
{
	return GetValueInternal<int>(VarName);
}

bool USlowAnimInstance::GetBool(FName VarName) const
{
	return GetValueInternal<bool>(VarName);
}

template<class T>
void USlowAnimInstance::SetValueInternal(FName VarName, T Value)
{
	FMyVariant* it = VariantMap.Find(VarName);
	if (it != nullptr) {
		if (!it->IsValidType<T>()) {
			UE_LOG(LogSlow, Error, TEXT("UPCAnimInstance::SetValueInternal(): Type T is not same to exist type."));
		}

		(*it) = Value;
	}
	else {
		VariantMap.Add(VarName, Value);
	}
}

template<class T>
T USlowAnimInstance::GetValueInternal(FName VarName) const
{
	const FMyVariant* it = VariantMap.Find(VarName);
	if (it != nullptr) {
		if (!it->IsValidType<T>()) {
			UE_LOG(LogSlow, Error, TEXT("UPCAnimInstance::GetValueInternal(): Type T is not same to exist type."));
		}

		return it->Get<T>();
	}
	else {
		return T();
	}
}
// Copyright 2020 Team slow. All right reserved.

#include "AnimInstance/SlowAnimInstance.h"

#include "Actor/SlowPlayableCharacter.h"
#include "Manager/WeaponManager.h"
#include "SlowGameInstance.h"
#include "AnimInstance/PCAnimInstance.h"

bool USlowAnimInstance::ManagerAccessibleState = false;

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

int USlowAnimInstance::GetCurrentWeaponNum() const
{

	if (USlowAnimInstance::ManagerAccessibleState && SlowPC != nullptr)
	{
		return SlowPC->GetCurrentWeaponNum();
	}


	return -2;
}

bool USlowAnimInstance::GetSwapAnimState() const
{

	if (USlowAnimInstance::ManagerAccessibleState && SlowPC != nullptr)
	{
		return SlowPC->GetSwapAinmState();
	}

	return false;
}

void USlowAnimInstance::SetManagerAccessibleState(const bool AccessState)
{
	USlowAnimInstance::ManagerAccessibleState = AccessState;
}

bool USlowAnimInstance::GetManagerAccessibleState()
{
	return ManagerAccessibleState;
}

bool USlowAnimInstance::TrySetSlowPC(ASlowPlayableCharacter *pc) const
{
	if (pc != nullptr)
	{
		if (SlowPC != pc)
		{
			SlowPC = pc;
		}
	}

	return SlowPC != nullptr ? true : false;
}
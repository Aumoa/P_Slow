// Copyright 2020 Team slow. All right reserved.

#include "AnimInstance/SlowAnimInstance.h"

#include "Actor/SlowPlayableCharacter.h"
#include "Manager/WeaponManager.h"
#include "SlowGameInstance.h"
#include "LogDefine.h"

bool USlowAnimInstance::ManagerAccessibleState = false;

USlowAnimInstance::USlowAnimInstance()
{

}

void USlowAnimInstance::NativeUpdateAnimation(float InDeltaSeconds)
{
	// 다음 애니메이션 업데이트를 수행하기 전 모든 트리거 부울 형식을 초기화합니다.
	for (auto& Item : VariantMap)
	{
		if (Item.Value.IsValidType<FTriggerBool>())
		{
			Item.Value.Get<FTriggerBool>().SetValue(false);
		}
	}

	Super::NativeUpdateAnimation(InDeltaSeconds);
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

void USlowAnimInstance::SetTrigger(FName VarName)
{
	FMyVariant* it = VariantMap.Find(VarName);
	if (it != nullptr)
	{
		if (!it->IsValidType<FTriggerBool>())
		{
			UE_LOG(LogSlow, Error, TEXT("UPCAnimInstance::GetValueInternal(): Type FTriggerBool is not same to exist type."));
			return;
		}

		auto& Value = it->Get<FTriggerBool>();
		Value.SetValue(true);
	}
	else
	{
		VariantMap.Add(VarName, FTriggerBool(true));
	}
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

bool USlowAnimInstance::GetTriggerBool(FName VarName) const
{
	return GetValueInternal<FTriggerBool>(VarName).GetValue();
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
	if (USlowAnimInstance::ManagerAccessibleState)
		if (SlowPC != nullptr)
			return SlowPC->GetCurrentWeaponNum();

	return -1;
}

bool USlowAnimInstance::GetSwapAnimState() const
{

	if (USlowAnimInstance::ManagerAccessibleState)
		if (SlowPC != nullptr)
			return SlowPC->GetSwapAinmState();

	return false;
}

bool USlowAnimInstance::GetIsFindInteractionObject() const
{
	if(USlowAnimInstance::ManagerAccessibleState)
	{
		if (SlowPC != nullptr)
		{
			return SlowPC->GetIsFindInteractionObject();
		}
	}

	return false;
}

bool USlowAnimInstance::GetRollAnimState() const
{
	if (USlowAnimInstance::ManagerAccessibleState)
	{
		if (SlowPC != nullptr)
		{
			return SlowPC->GetRollAnimState();
		}
	}

	return false;
}

bool USlowAnimInstance::GetIsBattle() const
{
	if (USlowAnimInstance::ManagerAccessibleState)
	{
		if (SlowPC != nullptr)
		{
			return SlowPC->GetIsBattle();
		}
	}

	return false;
}

void USlowAnimInstance::SetManagerAccessibleState(const bool AccessState)
{
	USlowAnimInstance::ManagerAccessibleState = AccessState;
}

bool USlowAnimInstance::GetManagerAccessibleState()
{
	return USlowAnimInstance::ManagerAccessibleState;
}

bool USlowAnimInstance::TrySetSlowPC(ASlowPlayableCharacter* pc) const
{
	if (SlowPC != pc)
	{
		SlowPC = pc;

		return true;
	}
		
	return false;
}

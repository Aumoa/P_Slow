// Copyright 2020 Team slow. All right reserved.

#include "Effect/StatModifyLinearEffect.h"

#include "LogDefine.h"
#include "Actor/SlowStatBasedCharacter.h"

FStatModifyLinearEffect::FStatModifyLinearEffect(AActor* InCaster)
{
	Caster = InCaster;
	ModifyValue = { };
}

FStatModifyLinearEffect::FStatModifyLinearEffect(AActor* InCaster, const FAttrInstance& InitModifyValue)
{
	Caster = InCaster;
	ModifyValue = InitModifyValue;
}

void FStatModifyLinearEffect::Apply(AActor* InTarget)
{
	auto StatBasedCharacter = Cast<ASlowStatBasedCharacter>(InTarget);
	if (StatBasedCharacter == nullptr)
	{
		UE_LOG(LogSlow, Error, TEXT("StatModifyLinearEffect::Apply(): InTarget 매개변수는 null이 될 수 없습니다."));
		return;
	}

	StatBasedCharacter->ApplyEffect(*this);
}

FAttrInstance FStatModifyLinearEffect::GetModifyValue() const
{
	return ModifyValue;
}

AActor* FStatModifyLinearEffect::GetCaster() const
{
	return Caster.Get();
}
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorEffect.h"

#include "Attributes/AttrInstance.h"

class AActor;

/// <summary>
/// 액터의 스탯에 선형 변화를 주는 이펙트 클래스입니다.
/// </summary>
class FStatModifyLinearEffect : public FActorEffect
{
	TWeakObjectPtr<AActor> Caster;
	FAttrInstance ModifyValue;

public:
	FStatModifyLinearEffect(AActor* InCaster);
	FStatModifyLinearEffect(AActor* InCaster, const FAttrInstance& InitModifyValue);

	/// <inheritdoc/>
	void Apply(AActor* InTarget) override;

	void SetModifyValue(const FAttrInstance& InModifyValue);
	FAttrInstance GetModifyValue() const;
	AActor* GetCaster() const;
};
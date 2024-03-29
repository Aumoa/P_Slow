﻿// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "AbilityBase.h"
#include "BehaviorAbility.h"
#include "IActorTargetAbility.h"

#include "Requirement/RequirementBase.h"

class ASlowCharacter;
class ASlowStatBasedCharacter;
class FActorEffect;


DECLARE_MULTICAST_DELEGATE(FDele_ImmediateEffect);
DECLARE_MULTICAST_DELEGATE(FDele_HitEffect);

/// <summary>
/// 기본 공격 어빌리티를 표현합니다.
/// </summary>
class FAttackAbility : virtual public FAbilityBase, virtual public IActorTargetAbility, public FBehaviorAbility<UBehavior>
{
	TWeakObjectPtr<ASlowCharacter> MyTarget = nullptr;

public:
	FDele_ImmediateEffect FAttackImmediateEffect;
	FDele_HitEffect FAttackHitEffect;

	FAttackAbility();
	bool ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer) override;
	void SetTarget(ASlowCharacter* InActor) override;
	TWeakObjectPtr<ASlowCharacter> GetTarget() override;

private:
	template<class T, typename TEnableIf<TIsDerivedFrom<T, FRequirementBase>::Value>::Type* _TypeChecker = nullptr>
	static TArray<T*> ExportSpecialClasses(const TArray<TSharedPtr<FRequirementBase>>& InRequirementBaseArray);
};
﻿// Copyright 2020 Team slow. All right reserved.

#include "Ability/AttackAbility.h"

#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"
#include "Actor/SlowStatBasedCharacter.h"
#include "Ability/WeaponBase.h"
#include "Requirement/ActorTargetRequirement.h"
#include "Components/Behavior.h"
#include "Effect/ActorEffect.h"

FAttackAbility::FAttackAbility()
{

}

bool FAttackAbility::ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer)
{
	if (!MyTarget.IsValid() || InCastPlayer == nullptr)
	{
		UE_LOG(LogSlow, Error, TEXT("%s: 타겟이 지정되지 않았거나 시전 플레이어가 null입니다."), __FUNCTIONT__);
		return false;
	}

	ASlowCharacter* const MyTargetResolve = MyTarget.Get();

	FEquipments Equips = InCastPlayer->GetCurrentEquipments();
	if (!Equips.Weapon.IsValid())
	{
		UE_LOG(LogSlow, Warning, TEXT("%s: 시전 플레이어가 공격에 적합한 무기를 소유하고 있지 않습니다. %s->GetCurrentEquipments()에서 반환되었습니다."), __FUNCTIONT__, nameof(InCastPlayer));
		return false;
	}

	UWeaponBase* const CurrentWeaponResolve = Equips.Weapon.Get();
	TArray<TSharedPtr<FRequirementBase>> Requirements = CurrentWeaponResolve->GetAllRequirements();



	// 무기 사용 요구 사항을 검사합니다.
	// 예: 재사용 대기시간 등
	bool bSelfCheck = true;
	for (int32 i = 0; i < Requirements.Num(); ++i)
	{
		if (!Requirements[i]->SelfCheck())
		{
			bSelfCheck = false;
			break;
		}
	}

	if (!bSelfCheck)
	{
		return false;
	}


	//공격 시도 시 발생하는 효과를 Broadcast합니다.
	if (FAttackImmediateEffect.IsBound())
	{
		FAttackImmediateEffect.Broadcast();
	}
	

	// 호철씨 개발 부분
	// 액터를 대상으로 하는 요구 사항을 검사합니다.
	TArray<FActorTargetRequirement*> ActorTargetRequirements = ExportSpecialClasses<FActorTargetRequirement>(Requirements);
	bool bActorCheck = true;
	for (int32 i = 0; i < ActorTargetRequirements.Num(); ++i)
	{
		if (!ActorTargetRequirements[i]->ActorTargetCheck(MyTargetResolve))
		{
			bActorCheck = false;
			break;
		}
	}

	if (!bActorCheck)
	{
		return false;
	}

	//
	// 공격 효과 인스턴스를 생성합니다.
	TSubclassOf<UBehavior> EffectClass = CurrentWeaponResolve->GetEffect();
	if (EffectClass == nullptr)
	{
		UE_LOG(LogSlow, Warning, TEXT("%s: 공격을 시도하려는 무기에 공격 효과가 없습니다. 오류는 아니지만, GetEffect() 함수가 오버라이드 되지 않았을 수 있습니다."), __FUNCTIONT__);
		return false;
	}

	auto EffectInstance = NewObject<UBehavior>(MyTargetResolve, EffectClass);
	if (EffectInstance == nullptr)
	{
		UE_LOG(LogSlow, Error, TEXT("%s: 공격을 시도하려는 무기에 공격 효과 클래스가 잘못 설정되었습니다. %s를 상속하는 올바른 클래스 값이 전달되어야 합니다."), __FUNCTIONT__, nameof_c(UBehavior));
		return false;
	}

	UE_LOG(LogSlow, Error, TEXT("%s. %s 전달 성공."), __FUNCTIONT__, nameof_c(UBehavior));

	EffectInstance->AddEffectList(CurrentWeaponResolve->GetEffectList());

	UE_LOG(LogSlow, Error, TEXT("이펙트 개수: %d"), EffectInstance->GetEffectCount());
	//
	// 공격 효과를 대상 캐릭터에 부여합니다.
	MyTargetResolve->AddOwnedComponent(EffectInstance);
	EffectInstance->RegisterComponent();
	//EffectInstance->PushActivate(true);

	//공격 성공 시 자신에게 발생하는 효과를 Broadcast합니다. (예:공속 버프)
	if (FAttackHitEffect.IsBound())
	{
		FAttackHitEffect.Broadcast();
	}

	return true;
}

void FAttackAbility::SetTarget(ASlowCharacter* InActor)
{
	MyTarget = InActor;
}

TWeakObjectPtr<ASlowCharacter> FAttackAbility::GetTarget()
{
	return MyTarget;
}

template<class T, typename TEnableIf<TIsDerivedFrom<T, FRequirementBase>::Value>::Type* _TypeChecker> //FRequirementBase를 상속 받았는지 체크
TArray<T*> FAttackAbility::ExportSpecialClasses(const TArray<TSharedPtr<FRequirementBase>>& InRequirementBaseArray)
{
	if (InRequirementBaseArray.Num() == 0)
	{
		return { };
	}

	TArray<T*> OutClasses;
	OutClasses.Reserve(InRequirementBaseArray.Num());

	for (int32 i = 0; i < InRequirementBaseArray.Num(); ++i)
	{
		T* CastIns = dynamic_cast<T*>(InRequirementBaseArray[i].Get());
		if (CastIns != nullptr)
		{
			OutClasses.Add(CastIns);
		}
	}

	return MoveTemp(OutClasses);
}
// Copyright 2020 Team slow. All right reserved.

#include "Ability/BehaviorAbility.h"

#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"
#include "Actor/SlowCharacter.h"
#include "Components/Behavior.h"

using namespace BehaviorAbility_details;

FBehaviorAbility_Impl::FBehaviorAbility_Impl(UClass* InBehaviorType)
{
	BehaviorType = InBehaviorType;
}

UClass* FBehaviorAbility_Impl::GetBehaviorType() const
{
	return BehaviorType;
}

UBehavior* FBehaviorAbility_Impl::AttachTo(ASlowCharacter* TargetCharacter)
{
	RemoveFrom(TargetCharacter);

	UBehavior* behavior = NewObject<UBehavior>(TargetCharacter, BehaviorType);
	if (behavior == nullptr) {
		FString className = BehaviorType->GetFName().ToString();
		UE_LOG(LogSlow, Error, TEXT("%s: Cannot create behavior component in type: %s"), __FUNCTIONT__, *className);
		return nullptr;
	}

	TargetCharacter->AddOwnedComponent(behavior);
	behavior->RegisterComponent();

	return behavior;
}

void FBehaviorAbility_Impl::RemoveFrom(ASlowCharacter* TargetCharacter)
{
	UBehavior* component = Cast<UBehavior>(TargetCharacter->GetComponentByClass(BehaviorType));
	if (component != nullptr) {
		component->RemoveFromParent();
	}
}
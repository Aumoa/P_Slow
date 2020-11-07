// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "AbilityBase.h"

class UBehavior;
class UClass;
class ASlowCharacter;

namespace BehaviorAbility_details
{
	class FBehaviorAbility_Impl
	{
		UClass* BehaviorType;

	public:
		FBehaviorAbility_Impl(UClass* InBehaviorType);

		UClass* GetBehaviorType() const;

		UBehavior* AttachTo(ASlowCharacter* TargetCharacter);
		void RemoveFrom(ASlowCharacter* TargetCharacter);
	};
}

template<class TBehaviorClass>
class FBehaviorAbility : virtual public FAbilityBase, public BehaviorAbility_details::FBehaviorAbility_Impl
{
	using Impl = BehaviorAbility_details::FBehaviorAbility_Impl;

	TSubclassOf<TBehaviorClass> BehaviorType;

public:
	FBehaviorAbility() : Impl(TBehaviorClass::StaticClass())
	{

	}

	TSubclassOf<TBehaviorClass> GetBehaviorType() const
	{
		return Impl::GetBehaviorType();
	}

protected:
	TBehaviorClass* AttachTo(ASlowCharacter* TargetCharacter)
	{
		return Cast<TBehaviorClass>(Impl::AttachTo(TargetCharacter));
	}

	void RemoveFrom(ASlowCharacter* TargetCharacter)
	{
		Impl::RemoveFrom(TargetCharacter);
	}
};
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "RequirementBase.h"

class AActor;

class FActorTargetRequirement : virtual public FRequirementBase
{
public:
	FActorTargetRequirement();

	/// <summary>
	/// 액터를 대상으로 하는 요구 사항의 충족 상태를 검사합니다.
	/// </summary>
	/// <param name="InActor"> 요구사항에 대한 액터 매개변수를 전달합니다. </param>
	/// <returns> 상태가 반환됩니다. </returns>
	virtual bool ActorTargetCheck(AActor* InActor) const;
};
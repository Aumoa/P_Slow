// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "EffectBase.h"

class AActor;

/// <summary>
/// 액터에 적용할 수 있는 이펙트에 대한 베이스 클래스입니다.
/// </summary>
class FActorEffect : public FEffectBase
{
protected:
	FActorEffect();

public:
	/// <summary>
	/// 이 효과를 적용합니다.
	/// </summary>
	/// <param name="InTarget"> 적용 대상 액터를 전달합니다. </param>
	virtual void Apply(AActor* InTarget) = 0;
};
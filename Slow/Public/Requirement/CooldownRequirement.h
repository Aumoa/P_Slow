// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "RequirementBase.h"

class FCooldownRequirement : public FRequirementBase
{
	float BaseCooldownInSeconds;
	float ActiveCooldownInSeconds;

public:
	FCooldownRequirement();

	/// <summary>
	/// 이 요구 사항의 재사용 대기 시간 값을 전달합니다.
	/// </summary>
	/// <param name="InCooldownInSeconds"> 시간을 초 단위로 전달합니다. </param>
	void SetupCooldown(float InCooldownInSeconds);

	/// <summary>
	/// 현재 진행 중인 재사용 대기 시간을 소비합니다.
	/// </summary>
	/// <param name="InDeltaSeconds"> 소비할 시간 값을 전달합니다. </param>
	/// <returns> <see cref="IsValid"/> 함수와 같은 반환 값을 가집니다. </returns>
	bool Consume(float InDeltaSeconds);

	/// <summary>
	/// 현재 진행 중인 재사용 대기 시간 값이 모두 소비되었는지 검사합니다.
	/// </summary>
	/// <returns> 결과가 반환됩니다. </returns>
	bool IsValid() const;

	/// <summary>
	/// <see cref="SetupCooldown"/> 함수로 설정 된 재사용 대기 시간 값으로 현재 재사용 대기 시간 값을 다시 설정합니다.
	/// </summary>
	void ResetCooldown();
};
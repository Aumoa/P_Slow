// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "RequirementBase.h"

class FCostRequirement : public FRequirementBase
{
	int32 ActiveUsageCount;
	int32 BaseUsageCount;
	bool CastChecker = false;

public:
	FCostRequirement();

	virtual bool SelfCheck() const override;

	/// <summary>
	/// 이 요구 사항의 사용 횟수 값을 전달합니다.
	/// </summary>
	/// <param name="InUsageCount"> 시간을 초 단위로 전달합니다. </param>
	void SetupUsageCount(float InUsageCount);

	/// <summary>
	/// 사용 횟수만큼 소비합니다.
	/// </summary>
	/// <param name="InDeltaSeconds"> 소비할 시간 값을 전달합니다. </param>
	/// <returns> <see cref="IsValid"/> 함수와 같은 반환 값을 가집니다. </returns>
	bool Consume(float InUsedCount);

	/// <summary>
	/// 현재 사용 횟수 값이 모두 소비되었는지 검사합니다.
	/// </summary>
	/// <returns> 결과가 반환됩니다. </returns>
	bool IsValid() const;

	/// <summary>
	/// <see cref="SetupCooldown"/> 함수로 설정 된 사용 횟수 값으로 현재 사용 횟수을 다시 설정합니다.
	/// </summary>
	void ResetUsageCount();
};
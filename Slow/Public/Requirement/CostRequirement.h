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
	/// �� �䱸 ������ ��� Ƚ�� ���� �����մϴ�.
	/// </summary>
	/// <param name="InUsageCount"> �ð��� �� ������ �����մϴ�. </param>
	void SetupUsageCount(float InUsageCount);

	/// <summary>
	/// ��� Ƚ����ŭ �Һ��մϴ�.
	/// </summary>
	/// <param name="InDeltaSeconds"> �Һ��� �ð� ���� �����մϴ�. </param>
	/// <returns> <see cref="IsValid"/> �Լ��� ���� ��ȯ ���� �����ϴ�. </returns>
	bool Consume(float InUsedCount);

	/// <summary>
	/// ���� ��� Ƚ�� ���� ��� �Һ�Ǿ����� �˻��մϴ�.
	/// </summary>
	/// <returns> ����� ��ȯ�˴ϴ�. </returns>
	bool IsValid() const;

	/// <summary>
	/// <see cref="SetupCooldown"/> �Լ��� ���� �� ��� Ƚ�� ������ ���� ��� Ƚ���� �ٽ� �����մϴ�.
	/// </summary>
	void ResetUsageCount();
};
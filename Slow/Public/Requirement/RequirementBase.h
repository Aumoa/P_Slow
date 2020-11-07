// Copyright 2020 Team slow. All right reserved.

#pragma once



class FRequirementBase
{
	uint8 bInvertCheck : 1;

public:
	FRequirementBase();

	/// <summary>
	/// 현재 요구 사항 충족 상태를 검사합니다.
	/// </summary>
	/// <returns> 상태가 반환됩니다. </returns>
	virtual bool SelfCheck() const;

	void SetInvertCheck(bool bFlag);
	bool IsInvertCheck() const;

protected:
	bool GetResult(bool bQueryRequireResult) const;
};
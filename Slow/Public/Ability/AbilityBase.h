// Copyright 2020 Team slow. All right reserved.

#pragma once

class ASlowStatBasedCharacter;

class FAbilityBase : public TSharedFromThis<FAbilityBase>
{
public:
	FAbilityBase();
	virtual ~FAbilityBase();

	virtual bool ExecuteIndirect(ASlowStatBasedCharacter* InCastPlayer);
	virtual void CancelIndirect();
};
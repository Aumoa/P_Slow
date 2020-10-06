// Copyright 2020 Team slow. All right reserved.

#include "Requirement/CooldownRequirement.h"

#include "LogDefine.h"

FCooldownRequirement::FCooldownRequirement()
{
	BaseCooldownInSeconds = 0;
	ActiveCooldownInSeconds = 0;
}

void FCooldownRequirement::SetupCooldown(float InCooldownInSeconds)
{
	if (InCooldownInSeconds < 0.0f) {
		UE_LOG(LogSlow, Warning, TEXT("FCooldownRequirement::SetupCooldown(): 매개 변수로 전달된 시간이 0초보다 작습니다. 즉시 시전을 표현하려면 0을 사용하십시오. 이 값은 0으로 설정됩니다. 설정된 값: %g"), InCooldownInSeconds);

		InCooldownInSeconds = 0;
	}

	BaseCooldownInSeconds = InCooldownInSeconds;
	ResetCooldown();
}

bool FCooldownRequirement::Consume(float InDeltaSeconds)
{
	bool bValid;

	ActiveCooldownInSeconds -= InDeltaSeconds;
	if (ActiveCooldownInSeconds <= 0) {
		ActiveCooldownInSeconds = 0;
		bValid = true;
	}
	else {
		bValid = false;
	}
	
	return GetResult(bValid);
}

bool FCooldownRequirement::IsValid() const
{
	bool bValid = ActiveCooldownInSeconds <= 0;
	return GetResult(bValid);
}

void FCooldownRequirement::ResetCooldown()
{
	ActiveCooldownInSeconds = BaseCooldownInSeconds;
}
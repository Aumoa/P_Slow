// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "SlowAIController.h"

#include "SlowMobController.generated.h"

class ASlowMobCharacterBase;

UCLASS()
class SLOW_API ASlowMobController : public ASlowAIController
{
	GENERATED_BODY()

private:
	uint8 bValidPossess : 1;
	TWeakObjectPtr<ASlowMobCharacterBase> MobCharacter;

public:
	ASlowMobController();

	void OnPossess(APawn* InTarget) override;
	void OnUnPossess() override;

	/// <summary>
	/// 현재 빙의되어있고, 빙의 대상이 올바른 몬스터 캐릭터인지 검사합니다.
	/// </summary>
	/// <returns> 검사 결과를 반환합니다. </returns>
	bool IsValidPossess() const;
};
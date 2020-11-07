// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "Attributes/CombatTag.h"

#include "SlowCharacter.generated.h"

class USlowAnimInstance;

UCLASS()
class SLOW_API ASlowCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// 이 두 변수는 GetAnimInstance에서 캐시된 데이터를 사용하기 위해
	// mutable 형식으로 사용합니다.
	mutable TWeakObjectPtr<USlowAnimInstance> SlowAnimInstance;
	mutable uint8 bCanAnimErrorLog : 1;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCombatTag CombatTag;

public:
	ASlowCharacter();

	void BeginPlay() override;

	void SetCombatTag(const FCombatTag& InCombatTag);
	FCombatTag GetCombatTag() const;

	USlowAnimInstance* GetAnimInstance() const;

private:
	void QueryAnimInstance() const;
};

// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AttributeInstance.generated.h"

UCLASS(BlueprintType)
class SLOW_API UAttributeInstance : public UObject
{
	GENERATED_BODY()

private:
	const struct FBaseAttributeConfig* configRef;

	int64 health;

public:
	void BeginPlay(const struct FBaseAttributeConfig& config);
	void ApplyDamage(const struct FRelativeDamage& relativeDamage);

	int64 GetCurrentHealth() const;

	bool IsPendingKill() const;
};
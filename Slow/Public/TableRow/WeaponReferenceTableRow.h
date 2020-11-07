// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "WeaponReferenceTableRow.generated.h"

class UUserWidget;


USTRUCT(BlueprintType)
struct FWeaponReferenceTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int64 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	int64 MaxUsageCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float UsageCountTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData")
	float SwapCoolDown;

};
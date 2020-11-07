// Copyright 2020. Team slow, All right reserved.

#pragma once



#include "WeaponBase.generated.h"

class FRequirementBase;
class UBehavior;
class UStaticMesh;
class UAnimMontage;
class UCapsuleComponent;

UCLASS(Blueprintable)
class SLOW_API UWeaponBase : public UObject
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 이 무기가 발동하기 위한 모든 요구 조건을 반환합니다.
	/// </summary>
	virtual TArray<TSharedPtr<FRequirementBase>> GetAllRequirements() const;

	/// <summary>
	/// 이 무기가 발동되면 대상에게 적용되는 효과를 가져옵니다.
	/// </summary>
	virtual TSubclassOf<UBehavior> GetEffect() const;
	
	virtual void BeginWeapon();
	virtual void EndWeapon();
	virtual bool SwapConditionInternal();
	virtual UStaticMesh* GetWeaponMesh();
	virtual FName GetSocketName();
	//가상함수 구현
	virtual int GetMaxComboCount();
	virtual UAnimMontage* GetAttackMontage();
	virtual TArray<FName> GetComboList();
	virtual UCapsuleComponent * GetCapsuleComponent();
};

// Copyright 2020. Team slow, All right reserved.

#pragma once


#include "Ability/WeaponBase.h"

#include "HammerWeapon.generated.h"

struct FWeaponReferenceTableRow;
class UAnimMontage;
class UCapsuleComponent;

UCLASS()
class SLOW_API UHammerWeapon : public UWeaponBase
{
	GENERATED_BODY()

private:
	UHammerWeapon();

	UPROPERTY()
	AActor* MyOwner;

	UPROPERTY()
	UStaticMesh *StaticMesh_Weapon;
	
	UPROPERTY()
	UCapsuleComponent* Collision_Weapon;

	UPROPERTY()
	FName SocketName;
	
	UPROPERTY()
	UAnimMontage *AttackMontage;

	UPROPERTY()
	TArray<FName> ComboList;

	TArray<TSharedPtr<FRequirementBase>> Requirements_Weapon;

public:
	FWeaponReferenceTableRow* WeaponReferenceTable;

public:
	void AddAttackImmediateEffect() override;
	void AddAttackHitEffect() override;

	void BeginWeapon(AActor *Owner) override;

	void EndWeapon() override;

	bool SwapConditionInternal() override;

	TArray<TSharedPtr<FRequirementBase>> GetAllRequirements() const override;

	TSubclassOf<UBehavior> GetEffect() const override;

	UStaticMesh* GetWeaponMesh() override;

	FName GetSocketName() override;

	int GetMaxComboCount() override;

	UAnimMontage* GetAttackMontage() override;
	TArray<FName> GetComboList() override;
	UCapsuleComponent* GetCapsuleComponent() override;
	FWeaponReferenceTableRow* GetWeaponDataTableRow() override;

	UFUNCTION()
	void ConsumeWeaponCost();
};

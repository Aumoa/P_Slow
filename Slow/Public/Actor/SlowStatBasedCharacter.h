// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "Actor/SlowCharacter.h"

#include "Attributes/BaseAttributeConfig.h"
#include "Attributes/AttrInstance.h"
#include "Attributes/Equipments.h"

#include "SlowStatBasedCharacter.generated.h"

struct FAttrInstance;
class FStatModifyLinearEffect;

UCLASS()
class SLOW_API ASlowStatBasedCharacter : public ASlowCharacter
{
	GENERATED_BODY()

protected:
	FAttrInstance AttrInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FBaseAttributeConfig InitialAttribute;	

public:
	ASlowStatBasedCharacter();

	void Tick(float DeltaTime) override;

	virtual FEquipments GetCurrentEquipments() const;

	FBaseAttributeConfig GetInitialAttribute() const;

	virtual void ApplyEffect(const FStatModifyLinearEffect& InEffect);
	FAttrInstance GetCurrentAttributes() const;

	virtual bool AddFaint(float num);
	virtual float GetBehaviorCoolDown() const;
	virtual void SetBehaviorCoolDown(float num);


	UFUNCTION(BlueprintCallable)
	float GetMaxHP();
	UFUNCTION(BlueprintCallable)
	float GetCurrentHP();

protected:
	void SetInitialAttribute(const FBaseAttributeConfig& InInitialAttribute);
	void BeginPlay() override;
	virtual void OnActorKill();

private:
	void StatValidCheck();
};
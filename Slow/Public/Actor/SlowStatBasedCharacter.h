// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
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

private:
	FAttrInstance AttrInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FBaseAttributeConfig InitialAttribute;

protected:
	void BeginPlay() override;

public:
	ASlowStatBasedCharacter();

	void Tick(float DeltaTime) override;

	virtual FEquipments GetCurrentEquipments() const;

	FBaseAttributeConfig GetInitialAttribute() const;

	virtual void ApplyEffect(const FStatModifyLinearEffect& InEffect);
	FAttrInstance GetCurrentAttributes() const;

protected:
	void SetInitialAttribute(const FBaseAttributeConfig& InInitialAttribute);

	virtual void OnActorKill();

private:
	void StatValidCheck();
};
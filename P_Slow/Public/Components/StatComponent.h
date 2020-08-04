// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Structures/BaseAttributeConfig.h"
#include "Attributes/AttributeInstance.h"

#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(HealthKilledDelegate, UStatComponent*);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class P_SLOW_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FAttributeInstance attributeInstance;

protected:
	UPROPERTY(EditAnywhere) FBaseAttributeConfig BaseAttribute;

public:
	// Sets default values for this component's properties
	UStatComponent();

public:
	void BeginPlay() override;
	//void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void ApplyDamage(const FRelativeDamage& Damage);

public:
	HealthKilledDelegate HealthKilled;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General") bool bBeginMaxCurrent;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaxAttribute") int64 MaxHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CurrentAttribute") int64 CurrentHealth;
};

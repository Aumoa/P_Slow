// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Structures/BaseAttributeConfig.h"

#include "StatComponent.generated.h"

class UAttributeInstance;

DECLARE_MULTICAST_DELEGATE_OneParam(HealthKilledDelegate, UStatComponent*);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLOW_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UAttributeInstance* AttrInstance;

protected:
	UPROPERTY(EditAnywhere)
	FBaseAttributeConfig baseAttribute;

public:
	// Sets default values for this component's properties
	UStatComponent();

public:
	void BeginPlay() override;
	//void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void ApplyDamage(const struct FRelativeDamage& relativeDamage);

public:
	HealthKilledDelegate HealthKilled;
};

// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Structures/Damage.h"

#include "StatAttribute.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P_SLOW_API UStatAttribute : public UActorComponent
{
	GENERATED_BODY()

private:
	DECLARE_MULTICAST_DELEGATE_OneParam( HealthKilledDelegate, UStatAttribute* );

public:	
	// Sets default values for this component's properties
	UStatAttribute();

public:
	void BeginPlay() override;
	//void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION( BlueprintCallable ) void ApplyDamage( const FDamage& Damage );

public:
	HealthKilledDelegate HealthKilled;

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "General" ) bool bBeginMaxCurrent;

protected:
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "MaxAttribute" ) int64 MaxHealth;
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "CurrentAttribute" ) int64 CurrentHealth;

private:
	void ApplyFixedDamage( const FDamage& Damage );
};

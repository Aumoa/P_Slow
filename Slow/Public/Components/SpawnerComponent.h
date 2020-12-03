// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SpawnerComponent.generated.h"

UENUM(BlueprintType)
enum class ESpawnerType : uint8
{
	Custom,
	Character
};

UCLASS(meta = (BlueprintSpawnable))
class SLOW_API USpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	uint8 bSpawnerTypeIsCustom : 1;

	UPROPERTY(EditAnywhere)
	ESpawnerType SpawnerType;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bSpawnerTypeIsCustom"))
	FString CustomKey;

public:
	USpawnerComponent();

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type Reason) override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;
#endif

	ESpawnerType GetType() const;
	FString GetCustomKey() const;

private:
#if WITH_EDITOR
	void OnChangeSpawnerTypeProperty();
#endif
};
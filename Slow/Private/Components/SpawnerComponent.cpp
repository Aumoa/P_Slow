// Copyright 2020 Team slow. All right reserved.

#include "Components/SpawnerComponent.h"

#include "Manager/SpawnManager.h"
#include "Common/SlowCommonMacros.h"

USpawnerComponent::USpawnerComponent()
{
	SpawnerType = ESpawnerType::Custom;

#if WITH_EDITOR
	OnChangeSpawnerTypeProperty();
#endif
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	SPAWN_MANAGER.AddSpawner(this);
}

void USpawnerComponent::EndPlay(const EEndPlayReason::Type Reason)
{
	SPAWN_MANAGER.RemoveSpawner(this);

	Super::EndPlay(Reason);
}

#if WITH_EDITOR

void USpawnerComponent::PostEditChangeProperty(FPropertyChangedEvent& InEvent)
{
	Super::PostEditChangeProperty(InEvent);

	const FName PropertyName = InEvent.GetPropertyName();

	if (PropertyName == nameof(SpawnerType))
	{
		OnChangeSpawnerTypeProperty();
	}
}

#endif

ESpawnerType USpawnerComponent::GetType() const
{
	return SpawnerType;
}

FString USpawnerComponent::GetCustomKey() const
{
#if WITH_EDITOR
	if (SpawnerType != ESpawnerType::Custom)
	{
		SLOW_LOG(Error, TEXT("Custom Key is not valid at spawner that is not custom type."));
	}
#endif

	return CustomKey;
}

#if WITH_EDITOR

void USpawnerComponent::OnChangeSpawnerTypeProperty()
{
	bSpawnerTypeIsCustom = SpawnerType == ESpawnerType::Custom;
}

#endif
// Copyright 2020 Team slow. All right reserved.

#include "Manager/SpawnManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "SlowPlayableCharacterState.h"
#include "Common/SlowCommonMacros.h"
#include "Actor/SlowPlayableCharacter.h"
#include "Datatable/ActorReference.h"
#include "Statics/SlowNavigationSystem.h"
#include "Components/SpawnerComponent.h"

ASlowPlayableCharacter* USpawnManager::SpawnPlayerPawn(FTransform Transform)
{
	auto instance = GetSingletonInstance();
	auto world = instance->GetWorld();

	if (world == nullptr) {
		SLOW_LOG(Error, TEXT("GameInstance haven't world context."));
		return nullptr;
	}

	TSubclassOf<AActor> _class = UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter"));
	FVector amendedLocation = Transform.GetLocation();

	if (FSlowNavigationSystem::FindActorStandableLocation(world, Cast<AActor>(_class->GetDefaultObject()), Transform.GetLocation(), &amendedLocation)) {
		Transform.SetLocation(amendedLocation);
	}

	return world->SpawnActor<ASlowPlayableCharacter>(UActorReference::GetReference(TEXT("Actor.SlowPlayableCharacter")), Transform);
}

void USpawnManager::AddSpawner(USpawnerComponent* InSpawner)
{
	if (InSpawner == nullptr)
	{
		SLOW_LOG(Error, TEXT("Argument is nullptr."));
		return;
	}

	ESpawnerType Type = InSpawner->GetType();
	if (Type == ESpawnerType::Custom)
	{
		FString CustomKey = InSpawner->GetCustomKey();
		CustomSpawners.Add(CustomKey, InSpawner);
	}
	else
	{
		Spawners.Add(Type, InSpawner);
	}
}

void USpawnManager::RemoveSpawner(USpawnerComponent* InSpawner)
{
	if (InSpawner == nullptr)
	{
		SLOW_LOG(Error, TEXT("Argument is nullptr."));
		return;
	}

	ESpawnerType Type = InSpawner->GetType();
	if (Type == ESpawnerType::Custom)
	{
		FString CustomKey = InSpawner->GetCustomKey();
		CustomSpawners.Remove(CustomKey);
	}
	else
	{
		Spawners.Remove(Type);
	}
}

FTransform USpawnManager::GetSpawnerTransformByType(ESpawnerType InType) const
{
	if (auto It = Spawners.Find(InType); It != nullptr)
	{
		return GetSpawnerTransform(*It);
	}

	SLOW_LOG(Error, TEXT("Cannot found spawner with type: (%s)%d."), nameof_c(ESpawnerType), (int32)InType);
	return FTransform::Identity;
}

FTransform USpawnManager::GetSpawnerTransformByCustomKey(const FString& InCustomKey) const
{
	if (auto It = CustomSpawners.Find(InCustomKey); It != nullptr)
	{
		return GetSpawnerTransform(*It);
	}

	SLOW_LOG(Error, TEXT("Cannot found spawner with custom key: %s."), *InCustomKey);
	return FTransform::Identity;
}

FTransform USpawnManager::GetSpawnerTransform(USpawnerComponent* Spawner) const
{
	AActor* const Actor = Spawner->GetOwner();

	if (Actor == nullptr)
	{
		SLOW_LOG(Error, TEXT("Spawner has not contained to actor."));
		return FTransform::Identity;
	}

	return Actor->GetActorTransform();
}

USpawnManager* USpawnManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<USpawnManager>();
}
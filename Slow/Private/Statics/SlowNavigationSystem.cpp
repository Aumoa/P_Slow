// Copyright 2020 Team slow. All right reserved.

#include "Statics/SlowNavigationSystem.h"

#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

namespace
{
	inline bool IsValidNavigationSystem(UNavigationSystemV1* InNavSys)
	{
		return InNavSys != nullptr && InNavSys->GetDefaultNavDataInstance() != nullptr;
	}

	inline const ANavigationData* GetNavigationData(UNavigationSystemV1* InNavSys, AActor* InActor, const FVector& PathStart)
	{
		const ANavigationData* navData = nullptr;

		if (InActor != nullptr) {
			INavAgentInterface* navAgent = Cast<INavAgentInterface>(InActor);

			if (navAgent != nullptr) {
				const FNavAgentProperties& agentProps = navAgent->GetNavAgentPropertiesRef();
				navData = InNavSys->GetNavDataForProps(agentProps, PathStart);
			}
			else {
				navData = Cast<ANavigationData>(InActor);
			}
		}

		if (navData == nullptr) {
			navData = InNavSys->GetDefaultNavDataInstance();
		}

		return navData;
	}

	template<class T>
	inline bool AssignIfValid(T* OutValue, const T& InValue)
	{
		if (OutValue != nullptr) {
			*OutValue = InValue;
			return true;
		}
		return false;
	}

	inline float GetCapsuleHalfHeightIfCharacter(AActor* InActor)
	{
		if (InActor == nullptr) {
			return 0.0f;
		}

		auto character = Cast<ACharacter>(InActor);
		if (character == nullptr) {
			return 0.0f;
		}

		UCapsuleComponent* capsuleComponent = character->GetCapsuleComponent();
		if (capsuleComponent == nullptr) {
			return 0.0f;
		}

		return capsuleComponent->GetScaledCapsuleHalfHeight();
	}
}

bool FSlowNavigationSystem::FindActorStandableLocation(AActor* InActor, FVector* OutStandableLocation)
{
	FVector location = InActor->GetActorLocation();

	return FindActorStandableLocation(InActor, InActor, location, OutStandableLocation);
}

bool FSlowNavigationSystem::FindActorStandableLocation(UObject* InWorldContext, AActor* InActor, const FVector& InLocation, FVector* OutStandableLocation)
{
	UWorld* world = InWorldContext->GetWorld();
	UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(world);

	AssignIfValid(OutStandableLocation, InLocation);

	bool bProjected = false;
	if (IsValidNavigationSystem(navSys)) {
		FNavLocation projected;
		const ANavigationData* navData = GetNavigationData(navSys, nullptr, FVector::ZeroVector);
		bProjected = navSys->ProjectPointToNavigation(InLocation, projected, FVector(500.0f, 500.0f, 500.0f), navData);

		if (bProjected) {
			float capsuleHalfHeight = GetCapsuleHalfHeightIfCharacter(InActor);

			AssignIfValid(OutStandableLocation, projected.Location + FVector(0, 0, capsuleHalfHeight));
		}
	}

	return bProjected;
}
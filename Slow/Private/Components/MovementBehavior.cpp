// Copyright 2020 Team slow. All right reserved.

#include "Components/MovementBehavior.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "LogDefine.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

UMovementBehavior::UMovementBehavior()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDirtyMark = true;
	bUseNavigationPath = false;
}

void UMovementBehavior::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = Cast<ACharacter>(GetOwner());
	MyMovementComponent = MyOwner->GetCharacterMovement();
}

void UMovementBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (MyMovementComponent.IsValid()) {
		if (bDirtyMark) {
			RebuildPaths();

			UCapsuleComponent* capsule = MyOwner->GetCapsuleComponent();
			ScaledCapsuleRadius = capsule->GetScaledCapsuleRadius();

			bDirtyMark = false;
		}

		if (!AddMove()) {
			RemoveFromParent();
		}
	}
}

void UMovementBehavior::SetActorDestination(const FVector& Dest, bool bFindNavigationPath)
{
	Goal = Dest;
	bUseNavigationPath = bFindNavigationPath;
	bDirtyMark = true;
}

void UMovementBehavior::RebuildPaths()
{
	MovementPaths.SetNum(0, false);

	AActor* actor = GetOwner();
	FVector startLocation = actor->GetActorLocation();

	if (bUseNavigationPath) {
		UNavigationPath* buildedPath = UNavigationSystemV1::FindPathToLocationSynchronously(
			actor->GetWorld(),
			startLocation,
			Goal,
			actor
		);

		if (buildedPath == nullptr) {
			UE_LOG(LogSlow, Warning, TEXT("UMovementBehavior::RebuildPaths(): Options that path building with navigation system is enabled but build paths failed. Use direct path instead."));
			bUseNavigationPath = false;
		}

		auto& paths = buildedPath->PathPoints;
		if (paths.Num() > 1) {
			MovementPaths.Append(paths.GetData() + 1, paths.Num() - 1);
		}
		else {
			// No move.
		}

		for (int32 i = 0; i < paths.Num(); ++i) {
			DrawDebugSphere(GetWorld(), paths[i], 5.0f, 5, FColor::Red, false, 5.0f);
		}
	}

	if (!bUseNavigationPath) {
		MovementPaths.Emplace(Goal);
	}

	FVector firstPathEnd = MovementPaths[0];
	LastDirection = firstPathEnd - startLocation;
	LastDirection.Normalize();
}

bool UMovementBehavior::AddMove()
{
	if (MovementPaths.Num() != 0) {

		FVector actorLocation = MyOwner->GetActorLocation();
		FVector currentDir = MovementPaths[0] - actorLocation;
		currentDir.Z = 0;

		//
		// Check that distance is smaller than critical value.
		if (currentDir.SizeSquared() < ScaledCapsuleRadius * ScaledCapsuleRadius) {
			UE_LOG(LogSlow, Log, TEXT("Front of movement path is removed with reason: Check that distance is smaller than critical value. Current path count: %d"), MovementPaths.Num());
			MovementPaths.RemoveAt(0);
			return AddMove();
		}

		//
		// Check that current location is exceed the goal of current path.
		else {
			currentDir.Normalize(1.0f);
			float cosAngleFromPrev = currentDir.CosineAngle2D(LastDirection);

			if (cosAngleFromPrev < -0.95f) {
				UE_LOG(LogSlow, Log, TEXT("Front of movement path is removed with reason: Check that current location is exceed the goal of current path. Current path count: %d"), MovementPaths.Num());
				MovementPaths.RemoveAt(0);
				return AddMove();
			}

			//
			// Move actor to next frame location.
			else {
				MyMovementComponent->AddInputVector(currentDir);

				LastDirection = currentDir;
				return true;
			}
		}
	}
	else {
		return false;
	}
}
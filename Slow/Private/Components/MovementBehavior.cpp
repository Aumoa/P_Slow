// Copyright 2020 Team slow. All right reserved.

#include "Components/MovementBehavior.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "LogDefine.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"

UMovementBehavior::UMovementBehavior()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDirtyMark = true;
	bUseNavigationPath = false;
}

void UMovementBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (MovementActor.IsValid()) {
		if (bDirtyMark) {
			RebuildPaths();
			bDirtyMark = false;
		}

		AddMove(DeltaTime);
	}
}

void UMovementBehavior::SetMovementActor(UCharacterMovementComponent* InMovementActor)
{
	MovementActor = InMovementActor;
}

UCharacterMovementComponent* UMovementBehavior::GetMovementActor() const
{
	return MovementActor.Get();
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

	AActor* actor = MovementActor->GetOwner();
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
	}

	if (!bUseNavigationPath) {
		MovementPaths.Emplace(Goal);
	}

	FVector firstPathEnd = MovementPaths[0];
	LastDirection = firstPathEnd - startLocation;
	LastDirection.Normalize();
}

void UMovementBehavior::AddMove(float DeltaTime)
{
	if (MovementPaths.Num() != 0) {
		AActor* actor = MovementActor->GetOwner();

		FVector actorLocation = actor->GetActorLocation();
		FVector currentDir = MovementPaths[0] - actorLocation;

		//
		// Check that distance is smaller than critical value.
		if (currentDir.SizeSquared() < 0.001f) {
			MovementPaths.RemoveAt(0);
			AddMove(DeltaTime);
		}

		//
		// Check that current location is exceed the goal of current path.
		else {
			currentDir.Normalize();
			float cosAngleFromPrev = currentDir.CosineAngle2D(LastDirection);

			if (cosAngleFromPrev < 0.95f) {
				MovementPaths.RemoveAt(0);
				AddMove(DeltaTime);
			}

			//
			// Move actor to next frame location.
			else {
				MovementActor->AddInputVector(currentDir * DeltaTime);
			}
		}
	}
}
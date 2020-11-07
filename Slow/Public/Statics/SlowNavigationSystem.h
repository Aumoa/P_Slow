// Copyright 2020 Team slow. All right reserved.

#pragma once



class AActor;

class FSlowNavigationSystem
{
public:
	static bool FindActorStandableLocation(AActor* InActor, FVector* OutStandableLocation);
	static bool FindActorStandableLocation(UObject* InWorldContext, AActor* InActor, const FVector& InLocation, FVector* OutStandableLocation);
};
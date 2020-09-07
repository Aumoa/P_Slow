// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ActorReference.generated.h"

class UDataTable;
class AActor;

UCLASS()
class SLOW_API UActorReference : public UObject
{
	GENERATED_BODY()

private:
	static TWeakObjectPtr<UDataTable> DataTable;

public:
	UActorReference();

	static TSubclassOf<AActor> GetReference(const FName& InReferenceKey);
};
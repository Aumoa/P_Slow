// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ActorReferenceTableRow.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FActorReferenceTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass;
};
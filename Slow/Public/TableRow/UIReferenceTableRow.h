// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "UIReferenceTableRow.generated.h"

class UUserWidget;

USTRUCT(BlueprintType)
struct FUIReferenceTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> WidgetClass;
};
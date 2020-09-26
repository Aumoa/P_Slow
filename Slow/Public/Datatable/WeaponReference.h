// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WeaponReference.generated.h"

class UDataTable;
struct FWeaponReferenceTableRow;

UCLASS()
class SLOW_API UWeaponReference : public UObject
{
	GENERATED_BODY()

private:
	static TWeakObjectPtr<UDataTable> DataTable;

public:
	UWeaponReference();

	static FWeaponReferenceTableRow* GetReferenceTableRow(const FName& InReferenceKey);

};
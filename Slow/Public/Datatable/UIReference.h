// Copyright 2020 Team slow. All right reserved.

#pragma once



#include "UIReference.generated.h"

class UDataTable;
class UUserWidget;

UCLASS()
class SLOW_API UUIReference : public UObject
{
	GENERATED_BODY()

private:
	static TWeakObjectPtr<UDataTable> DataTable;

public:
	UUIReference();

	static TSubclassOf<UUserWidget> GetReference(const FName& InReferenceKey);
};
// Copyright 2020 Team slow. All right reserved.

#include "Datatable/ActorReference.h"

#include "LogDefine.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "TableRow/ActorReferenceTableRow.h"

TWeakObjectPtr<UDataTable> UActorReference::DataTable;

UActorReference::UActorReference()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("/Game/Slow/Datatable/UI/DT_ActorReference"));
	checkf(dataTable.Succeeded(), TEXT("Cannot found datatable in /Game/Slow/Datatable/UI/DT_ActorReference."));
	DataTable = dataTable.Object;
}

TSubclassOf<AActor> UActorReference::GetReference(const FName& InReferenceKey)
{
	auto tableRow = DataTable->FindRow<FActorReferenceTableRow>(InReferenceKey, TEXT(""));
	if (tableRow == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("InReferenceKey from ActorReference table cannot be found."));
		return nullptr;
	}

	return tableRow->ActorClass;
}
// Copyright 2020 Team slow. All right reserved.

#include "Datatable/UIReference.h"

#include "LogDefine.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "TableRow/UIReferenceTableRow.h"

TWeakObjectPtr<UDataTable> UUIReference::DataTable;

UUIReference::UUIReference()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("/Game/Slow/Datatable/UI/DT_UIReference"));
	checkf(dataTable.Succeeded(), TEXT("Cannot found datatable in /Game/Slow/Datatable/UI/DT_UIReference."));
	DataTable = dataTable.Object;
}

TSubclassOf<UUserWidget> UUIReference::GetReference(const FName& InReferenceKey)
{
	auto tableRow = DataTable->FindRow<FUIReferenceTableRow>(InReferenceKey, TEXT(""));
	if (tableRow == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("InReferenceKey from UIReference table cannot be found."));
		return nullptr;
	}

	return tableRow->WidgetClass;
}
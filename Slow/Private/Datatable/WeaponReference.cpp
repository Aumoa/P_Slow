// Copyright 2020 Team slow. All right reserved.

#include "Datatable/WeaponReference.h"

#include "LogDefine.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "TableRow/WeaponReferenceTableRow.h"

TWeakObjectPtr<UDataTable> UWeaponReference::DataTable;

UWeaponReference::UWeaponReference()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("/Game/Slow/Datatable/Item/DT_WeaponReference"));
	checkf(dataTable.Succeeded(), TEXT("Cannot found datatable in /Game/Slow/Datatable/Item/DT_WeaponReference."));
	DataTable = dataTable.Object;
}

FWeaponReferenceTableRow* UWeaponReference::GetReferenceTableRow(const FName& InReferenceKey)
{
	auto tableRow = DataTable->FindRow<FWeaponReferenceTableRow>(InReferenceKey, TEXT(""));
	if (tableRow == nullptr) {
		UE_LOG(LogSlow, Error, TEXT("InReferenceKey from WeaponReference table cannot be found."));
		return nullptr;
	}

	return tableRow;
}
// Copyright 2020 Team slow. All right reserved.

#include "Datatable/WeaponReference.h"

#include "Common/SlowLogDefine.h"
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
		UE_LOG(LogSlow, Error, TEXT("%s from %s table cannot be found."), nameof(InReferenceKey), nameof_c(UWeaponReference));
		return nullptr;
	}

	return tableRow;
}
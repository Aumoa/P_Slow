// Copyright 2020 Team slow. All right reserved.

#include "Misc/LevelStreamingStatics.h"

#include "TableRow/SublevelGroup.h"
#include "Common/SlowCommonMacros.h"

UDataTable* ULevelStreamingStatics::DataTable;

ULevelStreamingStatics::ULevelStreamingStatics()
{
	static FString ReferencePath = TEXT("/Game/Slow/Datatable/SublevelGroup/DT_SublevelGroup.DT_SublevelGroup");
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableLoad(*ReferencePath);
	checkf(DataTableLoad.Succeeded(), TEXT("Cannot found datatable in \"%s\"."), *ReferencePath);
	DataTable = DataTableLoad.Object;

	CS_AsyncTaskResult = MakeUnique<FCriticalSection>();
}

void ULevelStreamingStatics::LoadSublevelGroup(UObject* InWorldContext, const FName& SublevelGroupName, TFunction<void()> CompletionCallback)
{
	auto Row = DataTable->FindRow<FSublevelGroup>(SublevelGroupName, TEXT(""));
	if (Row == nullptr)
	{
		SLOW_LOG(Error, TEXT("Cannot found row with name: %s in datatable[%s]."), *SublevelGroupName.ToString(), *DataTable->GetName());
		return;
	}

	TArray<FString> StreamingLevelsName = Row->SublevelsName;
	if (StreamingLevelsName.Num() == 0)
	{
		SLOW_LOG(Error, TEXT("Count of to need to load level is zero."));
		return;
	}

	// Save unload tasks and load tasks.
	TArray<FName> UnloadLevelTasks = MoveTemp(LastCommittedLevels);
	LastCommittedLevels.SetNum(StreamingLevelsName.Num());

	// Save async task configuration.
	AsyncLoadCallback = CompletionCallback;
	CompletedTasks = 0;
	NumAsyncTasks = UnloadLevelTasks.Num() + LastCommittedLevels.Num();

	for (int32 i = 0; i < LastCommittedLevels.Num(); ++i)
	{
		LastCommittedLevels[i] = *StreamingLevelsName[i];
	}

	// Unload preloaded levels.
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.UUID = 1;
	LatentActionInfo.Linkage = 0;
	LatentActionInfo.ExecutionFunction = nameof_f(AsyncTaskResult);

	for (auto& LevelName : UnloadLevelTasks)
	{
		UGameplayStatics::UnloadStreamLevel(InWorldContext, LevelName, LatentActionInfo, false);
		LatentActionInfo.UUID += 1;
	}

	// Load stream levels.
	for (auto& LevelName : LastCommittedLevels)
	{
		UGameplayStatics::LoadStreamLevel(InWorldContext, LevelName, true, false, LatentActionInfo);
		LatentActionInfo.UUID += 1;
	}
}

void ULevelStreamingStatics::AsyncTaskResult()
{
	ScopedLock(CS_AsyncTaskResult);

	CompletedTasks += 1;
	if (CompletedTasks == NumAsyncTasks && AsyncLoadCallback)
	{
		AsyncLoadCallback();
	}
}
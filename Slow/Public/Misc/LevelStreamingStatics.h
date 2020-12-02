// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "LevelStreamingStatics.generated.h"

UCLASS()
class SLOW_API ULevelStreamingStatics : public UObject
{
	GENERATED_BODY()

private:
	static UDataTable* DataTable;

	TArray<FName> LastCommittedLevels;

	TUniquePtr<FCriticalSection> CS_AsyncTaskResult;
	TFunction<void()> AsyncLoadCallback;
	int32 NumAsyncTasks;
	int32 CompletedTasks;

public:
	ULevelStreamingStatics();

	void LoadSublevelGroup(UObject* InWorldContext, const FName& SublevelGroupName, TFunction<void()> CompletionCallback);

private:
	UFUNCTION()
	void AsyncTaskResult();
};
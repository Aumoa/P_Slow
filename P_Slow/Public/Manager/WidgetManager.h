// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "Threading/Mutex.h"

#include "WidgetManager.generated.h"

class USlowGameInstance;
class UUserWidget;

UCLASS()
class P_SLOW_API UWidgetManager : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY() TArray<class UUserWidget*> AddedWidgets;
	TArray<bool> WidgetVisibleStates;
	TMap<FName, int64> WidgetsMap;

	TSharedPtr<FMutex> ThreadLocker;

	TQueue<int64> WaitingQueue;

public:
	static bool bClearAllWhenSceneChanged;

public:
	void Initialize( USlowGameInstance* GInstance );

	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static int64 AddWidget( UObject* This, UPARAM( ref ) const FName& WidgetName, class UUserWidget* UserWidget, bool bShow );
	static int64 AddWidget( UObject* This, UPARAM( ref ) const FName& WidgetName, UWorld* Owner, TSubclassOf<UUserWidget> UserWidgetClass, bool bShow );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static void ShowWidget( UObject* This, int64 WidgetLuid, bool bShow );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static bool RemoveWidget( UObject* This, int64 WidgetLuid );

	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static bool IsValidLuid( UObject* This, int64 WidgetLuid );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static bool IsShowWidget( UObject* This, int64 WidgetLuid );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static int64 FindWidget( UObject* This, UPARAM( ref ) const FName& WidgetName );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static UUserWidget* GetWidget( UObject* This, int64 WidgetLuid );

	inline static int64 AddWidget( UObject* This, UPARAM( ref ) const FName& WidgetName, TSubclassOf<UUserWidget> UserWidgetClass, bool bShow )
	{
		return AddWidget( This, WidgetName, This->GetWorld(), UserWidgetClass, bShow );
	}

private:
	void SetVisibleState( int64 CheckedWidgetLuid, bool bShow );
	int64 FindEmptyOrAlloc();

	UUserWidget* IsValidLuid( int64 WidgetLuid ) const;

	static UWidgetManager* GetSingletonInstance( UObject* This );
};

// Copyright 2020. Team slow, All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "ManagerBase.h"

#include "WidgetManager.generated.h"

class USlowGameInstance;
class UUserWidget;

UCLASS()
class P_SLOW_API UWidgetManager : public UManagerBase
{
	GENERATED_BODY()

private:
	UPROPERTY() TArray<class UUserWidget*> AddedWidgets;
	TArray<bool> WidgetVisibleStates;
	TMap<FName, int64> WidgetsMap;

	TQueue<int64> WaitingQueue;

public:
	static bool bClearAllWhenSceneChanged;

public:
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static int64 AddWidget( UPARAM( ref ) const FName& WidgetName, class UUserWidget* UserWidget, bool bShow );
	static int64 AddWidget( UPARAM( ref ) const FName& WidgetName, UWorld* Owner, TSubclassOf<UUserWidget> UserWidgetClass, bool bShow );

	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static void ShowWidget( int64 WidgetLuid, bool bShow );

	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static bool RemoveWidget( int64 WidgetLuid );

	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static bool IsValidLuid( int64 WidgetLuid );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static bool IsShowWidget( int64 WidgetLuid );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static int64 FindWidget( UPARAM( ref ) const FName& WidgetName );
	UFUNCTION( BlueprintCallable, Category = "WidgetManager" )
	static UUserWidget* GetWidget( int64 WidgetLuid );

	inline static int64 AddWidget( UPARAM( ref ) const FName& WidgetName, TSubclassOf<UUserWidget> UserWidgetClass, bool bShow )
	{
		return AddWidget( WidgetName, nullptr, UserWidgetClass, bShow );
	}

private:
	void SetVisibleState( int64 CheckedWidgetLuid, bool bShow );
	int64 FindEmptyOrAlloc();

	UUserWidget* IsValidLuidInternal( int64 WidgetLuid ) const;

	static UWidgetManager* GetSingletonInstance();
};

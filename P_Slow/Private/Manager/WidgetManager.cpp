// Copyright 2020. Team slow, All right reserved.

#include "Manager/WidgetManager.h"

#include "Blueprint/UserWidget.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"

#include "Kismet/GameplayStatics.h"

bool UWidgetManager::bClearAllWhenSceneChanged = true;

void UWidgetManager::Initialize( USlowGameInstance* GInstance )
{
	ThreadLocker = TSharedPtr<FMutex>( new FMutex() );
}

int64 UWidgetManager::AddWidget( UObject* This, const FName& WidgetName, UUserWidget* UserWidget, bool bShow )
{
	auto Instance = GetSingletonInstance( This );
	auto Context = Instance->ThreadLocker->Lock();

	if ( Instance->WidgetsMap.Contains( WidgetName ) )
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManager::AddWidget(): WidgetName is already exist." ) );
		return -1;
	}

	int64 Index = Instance->FindEmptyOrAlloc();

	if ( Index == -1 )
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManager::AddWidget(): Cannot allocate new element." ) );
		return -1;
	}

	Instance->AddedWidgets[Index] = UserWidget;
	Instance->SetVisibleState( Index, bShow );
	Instance->WidgetsMap.Emplace( WidgetName, Index );

	return Index;
}

int64 UWidgetManager::AddWidget( UObject* This, const FName& WidgetName, UWorld* Owner, TSubclassOf<UUserWidget> UserWidgetClass, bool bShow )
{
	return AddWidget( This, WidgetName, CreateWidget<UUserWidget>( Owner, UserWidgetClass, WidgetName ), bShow );
}

void UWidgetManager::ShowWidget( UObject* This, int64 WidgetLuid, bool bShow )
{
	auto Instance = GetSingletonInstance( This );
	auto Context = Instance->ThreadLocker->Lock();
	
	UUserWidget* Widget = nullptr;
	if ( ( Widget = Instance->IsValidLuid( WidgetLuid ) ) == nullptr )
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManager::ShowWidget(): WidgetLuid is invalid." ) );
		return;
	}

	Instance->SetVisibleState( WidgetLuid, bShow );
}

bool UWidgetManager::RemoveWidget( UObject* This, int64 WidgetLuid )
{
	auto Instance = GetSingletonInstance( This );
	auto Context = Instance->ThreadLocker->Lock();

	//
	// Cannot find reference. This is not error, but return false for notify to caller.
	if ( !Instance->IsValidLuid( WidgetLuid ) )
	{
		return false;
	}

	//
	// Remove reference. It will be removed from garbage collecting process.
	Instance->AddedWidgets[WidgetLuid] = nullptr;
	Instance->WidgetVisibleStates[WidgetLuid] = false;

	//
	// Find reference from map.
	bool bRemove = false;
	FName RemoveName;

	for ( const auto& Pair : Instance->WidgetsMap )
	{
		if ( Pair.Value == WidgetLuid )
		{
			bRemove = true;
			RemoveName = Pair.Key;
			break;
		}
	}

	if ( bRemove )
	{
		Instance->WidgetsMap.Remove( RemoveName );
	}

	//
	// Add this luid to waiting queue.
	Instance->WaitingQueue.Enqueue( WidgetLuid );

	return true;
}

bool UWidgetManager::IsValidLuid( UObject* This, int64 WidgetLuid )
{
	return GetSingletonInstance( This )->IsValidLuid( WidgetLuid ) != nullptr;
}

bool UWidgetManager::IsShowWidget( UObject* This, int64 WidgetLuid )
{
	auto Instance = GetSingletonInstance( This );

	if ( Instance->IsValidLuid( WidgetLuid ) )
	{
		return Instance->WidgetVisibleStates[WidgetLuid];
	}
	else
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManger::IsShowWidget(): WidgetLuid is invalid." ) );
		return false;
	}
}

int64 UWidgetManager::FindWidget( UObject* This, const FName& WidgetName )
{
	auto Instance = GetSingletonInstance( This );
	auto ReferencePtr = Instance->WidgetsMap.Find( WidgetName );

	if ( ReferencePtr == nullptr )
	{
		return -1;
	}
	else
	{
		return *ReferencePtr;
	}
}

UUserWidget* UWidgetManager::GetWidget( UObject* This, int64 WidgetLuid )
{
	auto Instance = GetSingletonInstance( This );

	if ( Instance->IsValidLuid( WidgetLuid ) )
	{
		return Instance->AddedWidgets[WidgetLuid];
	}
	else
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManager::GetWidget(): WidgetLuid is invalid." ) );
		return nullptr;
	}
}

void UWidgetManager::SetVisibleState( int64 CheckedWidgetLuid, bool bShow )
{
	if ( bShow != WidgetVisibleStates[CheckedWidgetLuid] )
	{
		auto Widget = AddedWidgets[CheckedWidgetLuid];

		if ( bShow )
		{
			Widget->AddToViewport();
		}
		else
		{
			Widget->RemoveFromParent();
		}

		WidgetVisibleStates[CheckedWidgetLuid] = bShow;
	}
}

int64 UWidgetManager::FindEmptyOrAlloc()
{
	if ( WaitingQueue.IsEmpty() )
	{
		int64 V = AddedWidgets.Num();
		AddedWidgets.Emplace( nullptr );
		WidgetVisibleStates.Emplace( false );
		return V;
	}
	else
	{
		int64 V = -1;
		WaitingQueue.Dequeue( V );
		return V;
	}
}

UUserWidget* UWidgetManager::IsValidLuid( int64 WidgetLuid ) const
{
	UUserWidget* Widget = nullptr;
	bool bExpression = AddedWidgets.Num() <= WidgetLuid || ( Widget = AddedWidgets[WidgetLuid] ) == nullptr;
	return Widget;
}

UWidgetManager* UWidgetManager::GetSingletonInstance( UObject* This )
{
	auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( This ) );
	return GameInstance->GetWidgetManager();
}
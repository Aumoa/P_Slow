// Copyright 2020 Team slow. All right reserved.

#include "Manager/WidgetManager.h"

#include "Blueprint/UserWidget.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"

#include "Kismet/GameplayStatics.h"

bool UWidgetManager::bClearAllWhenSceneChanged = true;

int64 UWidgetManager::AddWidget( const FName& WidgetName, UUserWidget* UserWidget, bool bShow )
{
	auto Instance = GetSingletonInstance();

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
	return 0;
}

int64 UWidgetManager::AddWidget( const FName& WidgetName, UWorld* Owner, TSubclassOf<UUserWidget> UserWidgetClass, bool bShow )
{
	if ( Owner == nullptr )
	{
		Owner = GetSingletonInstance()->GetWorld();
	}

	return AddWidget( WidgetName, CreateWidget<UUserWidget>( Owner, UserWidgetClass, WidgetName ), bShow );
	return 0;
}

void UWidgetManager::ShowWidget( int64 WidgetLuid, bool bShow )
{
	auto Instance = GetSingletonInstance();
	
	UUserWidget* Widget = nullptr;
	if ( ( Widget = Instance->IsValidLuidInternal( WidgetLuid ) ) == nullptr )
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManager::ShowWidget(): WidgetLuid is invalid." ) );
		return;
	}

	Instance->SetVisibleState( WidgetLuid, bShow );
}

bool UWidgetManager::RemoveWidget( int64 WidgetLuid )
{
	auto Instance = GetSingletonInstance();

	//
	// Cannot find reference. This is not error, but return false for notify to caller.
	if ( !Instance->IsValidLuidInternal( WidgetLuid ) )
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
	return false;
}

bool UWidgetManager::IsValidLuid( int64 WidgetLuid )
{
	return GetSingletonInstance()->IsValidLuidInternal( WidgetLuid ) != nullptr;
	return false;
}

bool UWidgetManager::IsShowWidget( int64 WidgetLuid )
{
	auto Instance = GetSingletonInstance();

	if ( Instance->IsValidLuidInternal( WidgetLuid ) )
	{
		return Instance->WidgetVisibleStates[WidgetLuid];
	}
	else
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManger::IsShowWidget(): WidgetLuid is invalid." ) );
		return false;
	}
	return false;
}

int64 UWidgetManager::FindWidget( const FName& WidgetName )
{
	auto Instance = GetSingletonInstance();
	auto ReferencePtr = Instance->WidgetsMap.Find( WidgetName );

	if ( ReferencePtr == nullptr )
	{
		return -1;
	}
	else
	{
		return *ReferencePtr;
	}
	return 0;
}

UUserWidget* UWidgetManager::GetWidget( int64 WidgetLuid )
{
	auto Instance = GetSingletonInstance();

	if ( Instance->IsValidLuidInternal( WidgetLuid ) )
	{
		return Instance->AddedWidgets[WidgetLuid];
	}
	else
	{
		UE_LOG( LogSlow, Error, TEXT( "UWidgetManager::GetWidget(): WidgetLuid is invalid." ) );
		return nullptr;
	}
	return nullptr;
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
	return 0;
}

UUserWidget* UWidgetManager::IsValidLuidInternal( int64 WidgetLuid ) const
{
	UUserWidget* Widget = nullptr;
	bool bExpression = AddedWidgets.Num() <= WidgetLuid || ( Widget = AddedWidgets[WidgetLuid] ) == nullptr;
	return Widget;
	return nullptr;
}

UWidgetManager* UWidgetManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UWidgetManager>();
	return nullptr;
}
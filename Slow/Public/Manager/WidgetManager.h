// Copyright 2020 Team slow. All right reserved.

#pragma once


#include "ManagerBase.h"

#include "WidgetManager.generated.h"

class USlowGameInstance;
class USlowWidgetBase;

UCLASS()
class SLOW_API UWidgetManager : public UManagerBase
{
	GENERATED_BODY()

public:
	static bool bClearAllWhenSceneChanged;

public:
	template<class T>
	static T* CreateSlowWidget(const FName& InReferenceKey, APlayerController* InPlayerController = nullptr, bool bVisible = true)
	{
		USlowWidgetBase* widget = CreateSlowWidgetInternal(InReferenceKey, InPlayerController, bVisible);
		return Cast<T>(widget);
	}
	
	template<class T>
	static T* CreateHUDWidget(const FName& InReferenceKey, bool bVisible = true)
	{
		USlowWidgetBase* widget = CreateHUDWidgetInternal(InReferenceKey, bVisible);
		return Cast<T>(widget);
	}

private:
	static USlowWidgetBase* CreateSlowWidgetInternal(const FName& InReferenceKey, APlayerController* InPlayerController, bool bVisible);
	static USlowWidgetBase* CreateHUDWidgetInternal(const FName& InReferenceKey,  bool bVisible);

	static UWidgetManager* GetSingletonInstance();
};

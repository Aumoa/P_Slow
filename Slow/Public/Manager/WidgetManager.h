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
	static UWidgetManager* SingletonInstance;

	uint8 bClearAllWhenSceneChanged : 1;

public:
	UWidgetManager();

	void Initialize(USlowGameInstance* GInstance) override;

	template<class T>
	T* CreateSlowWidget(const FName& InReferenceKey, APlayerController* InPlayerController = nullptr, bool bVisible = true)
	{
		USlowWidgetBase* widget = CreateSlowWidgetInternal(InReferenceKey, InPlayerController, bVisible);
		return Cast<T>(widget);
	}
	
	template<class T>
	T* CreateHUDWidget(const FName& InReferenceKey, bool bVisible = true)
	{
		USlowWidgetBase* widget = CreateHUDWidgetInternal(InReferenceKey, bVisible);
		return Cast<T>(widget);
	}

	static UWidgetManager* GetInstance();

private:
	USlowWidgetBase* CreateSlowWidgetInternal(const FName& InReferenceKey, APlayerController* InPlayerController, bool bVisible);
	USlowWidgetBase* CreateHUDWidgetInternal(const FName& InReferenceKey,  bool bVisible);
};

#define WIDGET_MANAGER (*UWidgetManager::GetInstance())
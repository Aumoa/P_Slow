// Copyright 2020 Team slow. All right reserved.

#include "Manager/WidgetManager.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Datatable/UIReference.h"
#include "UI/SlowWidgetBase.h"

USlowWidgetBase* UWidgetManager::CreateSlowWidgetInternal(const FName& InReferenceKey, APlayerController* InPlayerController, bool bVisible)
{
	USlowGameInstance* gameInstance = Super::GetGameInstance();

	if (InPlayerController == nullptr) {
		InPlayerController = UGameplayStatics::GetPlayerController(gameInstance->GetWorld(), 0);
	}

	TSubclassOf<UUserWidget> widgetClass = UUIReference::GetReference(InReferenceKey);
	USlowWidgetBase* widget = CreateWidget<USlowWidgetBase>(InPlayerController, widgetClass);

	if (bVisible) {
		widget->AddToViewport();
	}

	return widget;
}

UWidgetManager* UWidgetManager::GetSingletonInstance()
{
	return Super::GetSingletonInstance<UWidgetManager>();
}
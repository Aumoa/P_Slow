// Copyright 2020 Team slow. All right reserved.

#include "SlowGameInstance.h"

#include "Manager/SceneManager.h"
#include "Manager/SpawnManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/ConfigManager.h"
#include "Manager/InputManager.h"

void USlowGameInstance::InitializeManagers()
{
	Managers.Add(NewObject<UConfigManager>(this));
	Managers.Add(NewObject<USceneManager>(this));
	Managers.Add(NewObject<USpawnManager>(this));
	Managers.Add(NewObject<UWidgetManager>(this));
	Managers.Add(NewObject<UInputManager>(this));

	for (int32 i = 0, count = Managers.Num(); i < count; ++i) {
		Managers[i]->Initialize(this);
	}
}
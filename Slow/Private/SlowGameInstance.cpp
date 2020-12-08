// Copyright 2020 Team slow. All right reserved.

#include "SlowGameInstance.h"

#include "SlowConfig.h"
#include "Common/SlowLogDefine.h"
#include "Manager/ManagerBase.h"

USlowGameInstance* USlowGameInstance::Instance;

void USlowGameInstance::Init()
{
	Config = NewObject<USlowConfig>(this);

	Instance = this;
	InitializeManagers();
}

USlowConfig* USlowGameInstance::GetConfig() const
{
	return Config;
}

USlowGameInstance* USlowGameInstance::GetGameInstance()
{
	return Instance;
}

UManagerBase* USlowGameInstance::GetManager(TSubclassOf<UManagerBase> ClassType) const
{
	for (int32 i = 0, count = Managers.Num(); i < count; ++i) {
		if (Managers[i]->GetClass() == ClassType.Get()) {
			return Managers[i];
		}
	}

	checkfSlow(false, TEXT("%s: Unknown manager class."), __FUNCTIONT__);
	return nullptr;
}
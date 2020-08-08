// Copyright 2020 Team slow. All right reserved.


#include "SlowGameInstance.h"

#include "SlowConfig.h"
#include "LogDefine.h"

#include "Manager/ManagerBase.h"

USlowGameInstance* USlowGameInstance::Instance;

void USlowGameInstance::Startup()
{
	UE_LOG(LogSlow, Log, TEXT("USlowGameInstance::Startup()"));

	Instance = this;

	InitializeManagers();
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

	checkfSlow(false, TEXT("USlowGameInstance::GetManager(): Unknown manager class."));
	return nullptr;
}
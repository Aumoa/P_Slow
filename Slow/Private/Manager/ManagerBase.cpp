// Copyright 2020 Team slow. All right reserved.

#include "Manager/ManagerBase.h"

#include "SlowGameInstance.h"
#include "LogDefine.h"

USlowGameInstance* UManagerBase::GameInstance;

void UManagerBase::Initialize(USlowGameInstance* GInstance)
{
	GameInstance = GInstance;
}

UObject* UManagerBase::GetSingletonInstanceInternal(TSubclassOf<UManagerBase> ClassType)
{
	return GameInstance->GetManager(ClassType);
}
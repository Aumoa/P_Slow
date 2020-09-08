// Copyright 2020 Team slow. All right reserved.

#include "Controller/SlowControllerBase.h"

#include "Manager/SceneManager.h"

ASlowControllerBase::ASlowControllerBase()
{

}

void ASlowControllerBase::BeginPlay()
{
	Super::BeginPlay();

	USceneManager::BeginLevel(this);
}
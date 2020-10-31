// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayScene.h"

#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"

UGameplayScene::UGameplayScene()
{
	SetCursorVisibleOverride(false);
}

void UGameplayScene::SetNextStreamingLevel(const FName& InNextStreamingLevel)
{
	NextStreamingLevel = InNextStreamingLevel;
}

void UGameplayScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	USlowGameInstance* gameInstance = USlowGameInstance::GetGameInstance();
	FString currentName = UGameplayStatics::GetCurrentLevelName(gameInstance);
	if (currentName != TEXT("Map_1S")) {
		UGameplayStatics::OpenLevel(gameInstance, TEXT("Map_1S"));
	}
}

void UGameplayScene::EndPlay()
{
	Super::EndPlay();
}

FName UGameplayScene::GetNextStreamingLevel() const
{
	return NextStreamingLevel;
}
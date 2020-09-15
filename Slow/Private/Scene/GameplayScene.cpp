// Copyright 2020 Team slow. All right reserved.

#include "Scene/GameplayScene.h"

#include "SlowGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGameplayScene::SetNextStreamingLevel(const FName& InNextStreamingLevel)
{
	NextStreamingLevel = InNextStreamingLevel;
}

void UGameplayScene::BeginPlay(UObject* Args)
{
	Super::BeginPlay(Args);

	USlowGameInstance* gameInstance = USlowGameInstance::GetGameInstance();
	FString currentName = UGameplayStatics::GetCurrentLevelName(gameInstance);
	if (currentName != TEXT("Gameplay")) {
		UGameplayStatics::OpenLevel(gameInstance, TEXT("Gameplay"));
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
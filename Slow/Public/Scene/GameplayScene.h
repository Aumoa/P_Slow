// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Scene/SceneBase.h"

#include "GameplayScene.generated.h"

UCLASS()
class SLOW_API UGameplayScene : public USceneBase
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadWrite ) FName CurrentLevel;
	UPROPERTY( BlueprintReadWrite ) FName NextStreamingLevel;
	
public:
	void BeginPlay( UObject* Args = nullptr ) override;
	void EndPlay() override;

private:
	void ReadyPlayerCharacter();
};

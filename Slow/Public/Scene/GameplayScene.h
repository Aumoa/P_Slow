// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Scene/SceneBase.h"

#include "GameplayScene.generated.h"

UCLASS()
class SLOW_API UGameplayScene : public USceneBase
{
	GENERATED_BODY()

private:
	FName NextStreamingLevel;

protected:
	void SetNextStreamingLevel(const FName& InNextStreamingLevel);
	
public:
	UGameplayScene();

	void BeginPlay(UObject* Args = nullptr) override;
	void EndPlay() override;

	UFUNCTION(BlueprintPure)
	FName GetNextStreamingLevel() const;
};

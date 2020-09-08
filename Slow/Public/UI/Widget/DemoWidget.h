// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlowWidgetBase.h"

#include "DemoWidget.generated.h"

class UImage;
class UWidgetAnimation;

UCLASS()
class SLOW_API UDemoWidget : public USlowWidgetBase
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(UDemoWidget, FDemoEndedEvent);

private:
	float logoTickTime = 0.0f;

	UPROPERTY(meta = (BindWidget))
	UImage* LogoImage;

	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* Intro;

	UPROPERTY(EditAnywhere, Category = "AnimationTick", meta = (AllowPrivateAccess = "true"))
	float LogoTickPeriod = 0.1f;
	UPROPERTY(EditAnywhere, Category = "AnimationTick", meta = (AllowPrivateAccess = "true"))
	float LogoTickScale = 10.0f;

protected:
	UPROPERTY(EditAnywhere, Interp, Category = "AnimationTick")
	uint8 bLogoTickEnabled : 1;

protected:
	UFUNCTION(BlueprintCallable, Category = "Logo")
	void LogoTick(float deltaTime);

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& geometry, float deltaTime) override;

	FDemoEndedEvent DemoEnded;

private:
	void OnDemoSequenceEnded(UUMGSequencePlayer& InPlayer);
};
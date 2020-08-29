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

private:
	float logoTickTime = 0.0f;

	UPROPERTY(meta = (BindWidget))
	UImage* LogoImage;

	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* Intro;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Logo")
	uint8 bLogoTickEnabled : 1;

protected:
	UFUNCTION(BlueprintCallable, Category = "Logo")
	void LogoTick(float deltaTime);

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& geometry, float deltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	float LogoTickPeriod = 0.1f;
	UPROPERTY(EditAnywhere)
	float LogoTickScale = 10.0f;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Logo")
	UImage* OnGetLogoImage();
};
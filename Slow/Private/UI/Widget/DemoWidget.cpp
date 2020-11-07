// Copyright 2020 Team slow. All right reserved.

#include "UI/Widget/DemoWidget.h"

void UDemoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UUMGSequencePlayer* sequencePlayer = PlayAnimation(Intro);
	sequencePlayer->OnSequenceFinishedPlaying().AddUObject(this, &UDemoWidget::OnDemoSequenceEnded);
}

void UDemoWidget::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry, deltaTime);

	LogoTick(deltaTime);
}

void UDemoWidget::LogoTick(float deltaTime)
{
	if (bLogoTickEnabled) {
		logoTickTime += deltaTime * LogoTickScale;

		float logoTickPeriodScaled = LogoTickPeriod * LogoTickScale;
		int periodTickConverter = (int)(logoTickTime * (1.0f / logoTickPeriodScaled));
		float periodTick = (float)periodTickConverter * logoTickPeriodScaled;

		UMaterialInstanceDynamic* logoMaterial = LogoImage->GetDynamicMaterial();
		logoMaterial->SetScalarParameterValue(TEXT("ZagScalar"), periodTick);
	}
	else {
		UMaterialInstanceDynamic* logoMaterial = LogoImage->GetDynamicMaterial();
		logoMaterial->SetScalarParameterValue(TEXT("ZagScalar"), 0);
	}
}

void UDemoWidget::OnDemoSequenceEnded(UUMGSequencePlayer& InPlayer)
{
	DemoEnded.Broadcast();
}
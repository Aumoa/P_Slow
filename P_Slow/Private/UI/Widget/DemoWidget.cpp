// Copyright 2020 Team slow. All right reserved.

#include "UI/Widget/DemoWidget.h"

#include "Components/Image.h"

void UDemoWidget::LogoTick(float deltaTime)
{
	if (bLogoTickEnabled) {
		if (!logoImage.IsValid()) {
			logoImage = OnGetLogoImage();
		}

		logoTickTime += deltaTime * LogoTickScale;

		float logoTickPeriodScaled = LogoTickPeriod * LogoTickScale;
		int periodTickConverter = (int)(logoTickTime * (1.0f / logoTickPeriodScaled));
		float periodTick = (float)periodTickConverter * logoTickPeriodScaled;

		UMaterialInstanceDynamic* logoMaterial = logoImage->GetDynamicMaterial();
		logoMaterial->SetScalarParameterValue(TEXT("ZagScalar"), periodTick);
	}
}
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SokobanGameItem.h"

#include "SokobanGameObstacleItem.generated.h"

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameObstacleItem : public USokobanGameItem
{
	GENERATED_BODY()

public:
	USokobanGameObstacleItem();
};
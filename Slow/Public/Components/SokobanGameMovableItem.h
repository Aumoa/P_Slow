// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SokobanGameItem.h"

#include "SokobanGameMovableItem.generated.h"

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameMovableItem : public USokobanGameItem
{
	GENERATED_BODY()

public:
	USokobanGameMovableItem();
};
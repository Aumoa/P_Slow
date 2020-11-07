// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SokobanGameSlot.generated.h"

class USokobanGameItem;

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameSlot : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USokobanGameItem* MyItem = nullptr;

public:
	USokobanGameSlot();

	void SetItem(USokobanGameItem* InItem);
	USokobanGameItem* GetItem() const;
};
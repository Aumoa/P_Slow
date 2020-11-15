// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameSlot.h"

#include "Components/SokobanGameItem.h"

USokobanGameSlot::USokobanGameSlot()
{
	SetMobility(EComponentMobility::Movable);
}

void USokobanGameSlot::SetItem(USokobanGameItem* InItem)
{
	MyItem = InItem;
}

USokobanGameItem* USokobanGameSlot::GetItem() const
{
	return MyItem;
}
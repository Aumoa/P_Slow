// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameSlot.h"

#include "Components/SokobanGameItem.h"

USokobanGameSlot::USokobanGameSlot()
{
	SetMobility(EComponentMobility::Static);
}

void USokobanGameSlot::SetItem(USokobanGameItem* InItem)
{
	if (MyItem != nullptr)
	{
		MyItem->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}

	MyItem = InItem;

	if (MyItem != nullptr)
	{
		MyItem->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

USokobanGameItem* USokobanGameSlot::GetItem() const
{
	return MyItem;
}
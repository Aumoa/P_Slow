// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameItem.h"

#include "Common/SlowCommonMacros.h"
#include "Actor/SokobanGameActor.h"

USokobanGameItem::USokobanGameItem()
{
	SlotIndexX = 0;
	SlotIndexY = 0;
}

void USokobanGameItem::PostEditChangeProperty(FPropertyChangedEvent& InEvent)
{
	Super::PostEditChangeProperty(InEvent);

	const FName PropertyName = InEvent.GetPropertyName();

	if (PropertyName == nameof(SlotIndexX))
	{
		SetSlotIndexX(SlotIndexX);
	}

	else if (PropertyName == nameof(SlotIndexY))
	{
		SetSlotIndexY(SlotIndexY);
	}
}

int32 USokobanGameItem::GetSlotIndexX() const
{
	return SlotIndexX;
}

void USokobanGameItem::SetSlotIndexX(int32 InValue)
{
	SlotIndexX = InValue;
	UpdateSlot();
}

int32 USokobanGameItem::GetSlotIndexY() const
{
	return SlotIndexY;
}

void USokobanGameItem::SetSlotIndexY(int32 InValue)
{
	SlotIndexY = InValue;
	UpdateSlot();
}

void USokobanGameItem::UpdateSlot()
{
	auto MyActor = Cast<ASokobanGameActor>(GetOwner());
	if (MyActor == nullptr)
	{
		SLOW_LOG(Error, TEXT("%s 컴포넌트는 반드시 %s 액터에 배치되어야 합니다."), nameof_c(USokobanGameItem), nameof_c(ASokobanGameActor));
	}

	MyActor->CheckSlotItem(this);
}
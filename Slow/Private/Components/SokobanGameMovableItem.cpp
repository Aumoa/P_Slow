// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameMovableItem.h"

#include "Actor/SokobanGameActor.h"

USokobanGameMovableItem::USokobanGameMovableItem()
{

	PrimaryComponentTick.bCanEverTick = true;

	InteropSpeed = 100.0f;

	CurDestLocation = FVector2D::ZeroVector;
	bMoving = false;
}

void USokobanGameMovableItem::BeginPlay()
{
	Super::BeginPlay();

	auto [X, Y, Z] = GetRelativeLocation();
	CurDestLocation = { X, Y };
}

void USokobanGameMovableItem::TickComponent(float InDeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
{
	Super::TickComponent(InDeltaSeconds, TickType, TickFunction);

	if (bMoving)
	{
		FVector MyLocation3D = GetRelativeLocation();
		FVector2D MyLocation = { MyLocation3D.X, MyLocation3D.Y };

		FVector2D MovingDirection = CurDestLocation - MyLocation;
		float MovingLength = MovingDirection.Size();
		MovingDirection.Normalize();
		float DeltaInteropSpeed = InDeltaSeconds * InteropSpeed;

		// 남은 거리가 이동할 거리보다 작을 경우
		if (MovingLength < DeltaInteropSpeed)
		{
			SetRelativeLocation(Select(CurDestLocation, 0, 0, 1, MyLocation3D));
			bMoving = false;
		}
		else
		{
			const FVector2D Delta = MovingDirection * DeltaInteropSpeed;
			SetRelativeLocation(Select(MyLocation + Delta, 0, 0, 1, MyLocation3D));
		}
	}
}

bool USokobanGameMovableItem::IsMoving() const
{
	return bMoving;
}

void USokobanGameMovableItem::UpdateLocation()
{
	CurDestLocation = GetActor()->QuerySlotLocation(GetSlotIndexX(), GetSlotIndexY());
	if (HasBegunPlay())
	{
		bMoving = true;
	}
	else
	{
		FVector MyRelativeLocation = GetRelativeLocation();
		SetRelativeLocation(Select(MyRelativeLocation, 1, 1, 0, CurDestLocation));
	}
}

template<class First, class Second>
FVector USokobanGameMovableItem::Select(const First& InFirstItem, int32 X, int32 Y, int32 Z, const Second& InSecondItem)
{
	return FVector(
		X == 0 ? InFirstItem[0] : InSecondItem[0],
		Y == 0 ? InFirstItem[1] : InSecondItem[1],
		Z == 0 ? InFirstItem[2] : InSecondItem[2]
	);
}
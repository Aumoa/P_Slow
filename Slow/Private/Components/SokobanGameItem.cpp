// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameItem.h"

#include "Common/SlowCommonMacros.h"
#include "Actor/SokobanGameActor.h"

USokobanGameItem::USokobanGameItem()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	SlotIndexX = 0;
	SlotIndexY = 0;
	InteropSpeed = 100.0f;

	CurDestLocation = FVector2D::ZeroVector;
	bMoving = false;
}

void USokobanGameItem::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	MyActor = Cast<ASokobanGameActor>(MyOwner);

	if (!MyActor.IsValid())
	{
		SLOW_LOG(Error, TEXT("컴포넌트의 소유자가 %s 형식이 아닙니다."), nameof_c(ASokobanGameActor));
	}

	// 컴포넌트의 시작 위치를 설정합니다.
	FVector2D StartLocation = MyActor->QuerySlotLocation(SlotIndexX, SlotIndexY);
	FVector MyLocation = GetRelativeLocation();
	//SetRelativeLocation(Select(StartLocation, 0, 0, 1, MyLocation));
	bMoving = true;

	CurDestLocation = StartLocation;
}

void USokobanGameItem::TickComponent(float InDeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
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

			SetSlotIndexX(SlotIndexX == 0 ? 9 : 0);
			SetSlotIndexY(SlotIndexY == 0 ? 9 : 0);
		}
		else
		{
			const FVector2D Delta = MovingDirection * DeltaInteropSpeed;
			SetRelativeLocation(Select(MyLocation + Delta, 0, 0, 1, MyLocation3D));
		}
	}
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

	bMoving = true;
	CurDestLocation = MyActor->QuerySlotLocation(SlotIndexX, SlotIndexY);
}

int32 USokobanGameItem::GetSlotIndexY() const
{
	return SlotIndexY;
}

void USokobanGameItem::SetSlotIndexY(int32 InValue)
{
	SlotIndexY = InValue;
	UpdateSlot();

	bMoving = true;
	CurDestLocation = MyActor->QuerySlotLocation(SlotIndexX, SlotIndexY);
}

bool USokobanGameItem::IsMoving() const
{
	return bMoving;
}

void USokobanGameItem::UpdateSlot()
{
	auto MyOwner = Cast<ASokobanGameActor>(GetOwner());
	if (MyOwner == nullptr)
	{
		SLOW_LOG(Error, TEXT("%s 컴포넌트는 반드시 %s 액터에 배치되어야 합니다."), nameof_c(USokobanGameItem), nameof_c(ASokobanGameActor));
	}

	MyOwner->CheckSlotItem(this);
}

template<class First, class Second>
FVector USokobanGameItem::Select(const First& InFirstItem, int32 X, int32 Y, int32 Z, const Second& InSecondItem)
{
	return FVector(
		X == 0 ? InFirstItem[0] : InSecondItem[0],
		Y == 0 ? InFirstItem[1] : InSecondItem[1],
		Z == 0 ? InFirstItem[2] : InSecondItem[2]
	);
}
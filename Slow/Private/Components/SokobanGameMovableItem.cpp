// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameMovableItem.h"

#include "Actor/SokobanGameActor.h"
#include "Controller/SlowPlayerController.h"
#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"

USokobanGameMovableItem::USokobanGameMovableItem()
{
	InteropSpeed = 300.0f;

	CurDestLocation = FVector2D::ZeroVector;
	bMoving = false;
	bRetryRequest = false;
}

void USokobanGameMovableItem::BeginPlay()
{
	Super::BeginPlay();

	auto [X, Y, Z] = GetRelativeLocation();
	CurDestLocation = { X, Y };
}

bool USokobanGameMovableItem::OnHitInteractionRay(AActor* InEventSender, FHitResult& InRemoteHitResult)
{
	FVector FourDirection[4] =
	{
		TwoDirection[Dir_Forward],
		TwoDirection[Dir_Right],
		-TwoDirection[Dir_Right],
		-TwoDirection[Dir_Forward]
	};

	// 히트 임팩트 방향과 가장 가까운 방향을 찾습니다.
	float MinimumCosAngle = -1.0f;
	int32 ChoosedIndex = -1;
	for (int32 i = 0; i < UE_ARRAY_COUNT(FourDirection); ++i)
	{ 
		float CosAngle = FourDirection[i] | InRemoteHitResult.ImpactNormal;
		if (CosAngle > MinimumCosAngle)
		{
			MinimumCosAngle = CosAngle;
			ChoosedIndex = i;
		}
	}

	static TTuple<int32, int32> FourOffset[4] =
	{
		TTuple<int32, int32>(-1,  0),
		TTuple<int32, int32>(0, -1),
		TTuple<int32, int32>(0,  1),
		TTuple<int32, int32>(1,  0)
	};

	auto [SelectX, SelectY] = FourOffset[ChoosedIndex];
	int32 MoveX = GetSlotIndexX() + SelectX;
	int32 MoveY = GetSlotIndexY() + SelectY;

	GetActor()->MoveSlotItem(this, MoveX, MoveY);

	// 이동이 가능하든 불가능하든, 상호 작용 히트 자체는 성공했습니다.
	return true;
}

void USokobanGameMovableItem::CustomTick(float InDeltaSeconds)
{
	Super::CustomTick(InDeltaSeconds);

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

bool USokobanGameMovableItem::HasUpdating() const
{
	return IsMoving() || Super::HasUpdating();
}

bool USokobanGameMovableItem::IsMoving() const
{
	return bMoving;
}

void USokobanGameMovableItem::UpdateLocation(bool bForceMove)
{
	CurDestLocation = GetActor()->QuerySlotLocation(GetSlotIndexX(), GetSlotIndexY());
	if (!bForceMove && HasBegunPlay())
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
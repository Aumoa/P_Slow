// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameItem.h"

#include "Common/SlowCommonMacros.h"
#include "Actor/SokobanGameActor.h"
#include "Common/SlowCollisionProfile.h"

USokobanGameItem::USokobanGameItem()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetMobility(EComponentMobility::Movable);

	SlotIndexX = 0;
	SlotIndexY = 0;
	ConstSlotIndexX = 0;
	ConstSlotIndexY = 0;

	TwoDirection[0] = FVector::ZeroVector;
	TwoDirection[1] = FVector::ZeroVector;

	SetCollisionProfileName(CollisionProfile::InteractionOnly);
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
	FVector2D StartLocation = GetActor()->QuerySlotLocation(SlotIndexX, SlotIndexY);
	FVector MyLocation = GetRelativeLocation();
	SetRelativeLocation(Select(StartLocation, 0, 0, 1, MyLocation));

	FRotator MyRotator = GetComponentRotation();
	TwoDirection[Dir_Forward] = MyRotator.RotateVector(FVector::ForwardVector);
	TwoDirection[Dir_Right] = MyRotator.RotateVector(FVector::RightVector);

	ConstSlotIndexX = SlotIndexX;
	ConstSlotIndexY = SlotIndexY;
}

bool USokobanGameItem::OnHitInteractionRay(AActor* InEventSender, FHitResult& InRemoteHitResult)
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
		TTuple<int32, int32>( 0, -1),
		TTuple<int32, int32>( 0,  1),
		TTuple<int32, int32>( 1,  0)
	};
	
	auto [SelectX, SelectY] = FourOffset[ChoosedIndex];
	int32 MoveX = GetSlotIndexX() + SelectX;
	int32 MoveY = GetSlotIndexY() + SelectY;

	bool bMovable = MyActor->CheckIndexMovable(MoveX, MoveY);
	if (bMovable)
	{
		SetSlotIndexX(MoveX);
		SetSlotIndexY(MoveY);
	}

	// 이동이 가능하든 불가능하든, 상호 작용 히트 자체는 성공했습니다.
	return true;
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
	if (SlotIndexX != InValue || !HasBegunPlay())
	{
		SlotIndexX = InValue;
		UpdateSlot();
		UpdateLocation();
	}
}

int32 USokobanGameItem::GetSlotIndexY() const
{
	return SlotIndexY;
}

void USokobanGameItem::SetSlotIndexY(int32 InValue)
{
	if (SlotIndexY != InValue || !HasBegunPlay())
	{
		SlotIndexY = InValue;
		UpdateSlot();
		UpdateLocation();
	}
}

void USokobanGameItem::Retry()
{
	SlotIndexX = ConstSlotIndexX;
	SlotIndexY = ConstSlotIndexY;

	UpdateLocation(true);
}

void USokobanGameItem::UpdateLocation(bool bForceMove)
{
	UNREFERENCED_PARAMETER(bForceMove);

	FVector2D DestLocation = GetActor()->QuerySlotLocation(SlotIndexX, SlotIndexY);
	FVector MyRelativeLocation = GetRelativeLocation();
	SetRelativeLocation(Select(MyRelativeLocation, 1, 1, 0, DestLocation));
}

ASokobanGameActor* USokobanGameItem::GetActor() const
{
	if (!MyActor.IsValid())
	{
		MyActor = Cast<ASokobanGameActor>(GetOwner());
	}
	return MyActor.Get();
}

void USokobanGameItem::UpdateSlot()
{
	auto MyOwner = Cast<ASokobanGameActor>(GetOwner());
	if (MyOwner == nullptr)
	{
		SLOW_LOG(Error, TEXT("%s 컴포넌트는 반드시 %s 액터에 배치되어야 합니다."), nameof_c(USokobanGameItem), nameof_c(ASokobanGameActor));
	}

	MyOwner->CheckSlotItem(this);
	MyOwner->ConsumeMove();
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
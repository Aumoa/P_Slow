// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameItem.h"

#include "Common/SlowCommonMacros.h"
#include "Actor/SokobanGameActor.h"
#include "Common/SlowCollisionProfile.h"
#include "Components/SokobanGameSlot.h"

USokobanGameItem::USokobanGameItem()
{
	PrimaryComponentTick.bCanEverTick = false;

	bHasUpdating = false;

	SetMobility(EComponentMobility::Movable);

	SlotIndexX = 0;
	SlotIndexY = 0;
	ConstSlotIndexX = 0;
	ConstSlotIndexY = 0;

	CurrentSlot = nullptr;

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

#if WITH_EDITOR

void USokobanGameItem::PostEditChangeProperty(FPropertyChangedEvent& InEvent)
{
	Super::PostEditChangeProperty(InEvent);

	const FName PropertyName = InEvent.GetPropertyName();

	if (PropertyName == nameof(SlotIndexX))
	{
		MyActor->MoveSlotItem(this, SlotIndexX, SlotIndexY);
	}

	else if (PropertyName == nameof(SlotIndexY))
	{
		MyActor->MoveSlotItem(this, SlotIndexX, SlotIndexY);
	}
}

#endif

void USokobanGameItem::CustomTick(float InDeltaSeconds)
{
	if (DestructLimitTime.IsReached())
	{
		bHasUpdating = false;
	}
	else
	{
		DestructLimitTime.Tick(InDeltaSeconds);
	}
}

void USokobanGameItem::Retry()
{
	UDestructibleMesh* MyMesh = GetDestructibleMesh();
	SetDestructibleMesh(nullptr);
	SetDestructibleMesh(MyMesh);

	SetCollisionProfileName(CollisionProfile::InteractionOnly);

	ReregisterComponent();

	SlotIndexX = ConstSlotIndexX;
	SlotIndexY = ConstSlotIndexY;

	MyActor->MoveSlotItem(this, ConstSlotIndexX, ConstSlotIndexY, true);
	UpdateLocation(true);
}

void USokobanGameItem::DestructItem()
{
	SetCollisionProfileName(CollisionProfile::NoCollision);

	ApplyRadiusDamage(1000.0f, GetComponentLocation(), 1.0f, 1.0f, true);
	bHasUpdating = true;
	DestructLimitTime.Reset(3.0f);
}

bool USokobanGameItem::HasUpdating() const
{
	return bHasUpdating;
}

USokobanGameSlot* USokobanGameItem::GetCurrentSlot() const
{
	return CurrentSlot;
}

int32 USokobanGameItem::GetSlotIndexX() const
{
	return SlotIndexX;
}

int32 USokobanGameItem::GetSlotIndexY() const
{
	return SlotIndexY;
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

void USokobanGameItem::RemoveSlotReference()
{
	if (CurrentSlot != nullptr)
	{
		CurrentSlot->SetItem(nullptr);
		CurrentSlot = nullptr;
	}
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
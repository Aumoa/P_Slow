// Copyright 2020 Team slow. All right reserved.

#include "Actor/SokobanGameActor.h"

#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"
#include "Components/SokobanGameSlot.h"
#include "Components/SokobanGameItem.h"

#define CHECK_ITEM_COUNT(XY, Min, Max, ...) \
if (XY < Min)\
{\
	UE_LOG(LogSlow, Error, TEXT("%s: %s의 값은 %d보다 크거나 같아야 합니다.(%d)"), __FUNCTIONT__, nameof(XY), Min, XY);\
	return __VA_ARGS__;\
}\
\
else if (XY > Max)\
{\
	UE_LOG(LogSlow, Error, TEXT("%s: %s의 값은 %d보다 작거나 같아야 합니다.(%d)"), __FUNCTIONT__, nameof(XY), Max, XY);\
	return __VA_ARGS__;\
}

#define AssignIfValid(X, Y) if (X != nullptr) { *(X) = (Y); }

#define RegisterPropertyChanged(VarName)\
if (PropertyName == nameof(VarName))\
{\
	OnPropertyChanged_##VarName();\
}

ASokobanGameActor::ASokobanGameActor()
{
	bRefreshed = false;

	ItemCountX = 10;
	ItemCountY = 10;

	Root = CreateDefaultSubobject<USceneComponent>(nameof(RootComponent));
	Root->SetMobility(EComponentMobility::Movable);
	SetRootComponent(Root);

	SlotMesh = nullptr;
	CellWidth = 100.0f;
	CellHeight = 100.0f;
	SlotMeshScale = FVector(1.0f, 1.0f, 1.0f);
}

void ASokobanGameActor::BeginPlay()
{
	Super::BeginPlay();

	if (!bRefreshed)
	{
		OnPropertyChanged_ItemCount();
	}

	// 모든 하위 컴포넌트 중에서 USokobanGameItem 컴포넌트를 검색합니다.
	const TSet<UActorComponent*>& AllComponents = GetComponents();
	ItemComponents.Reserve(AllComponents.Num());

	TSet<TPair<int32, int32>> DuplicationChecker;
	for (auto& Item : AllComponents)
	{
		auto ItemComponent = Cast<USokobanGameItem>(Item);
		if (ItemComponent != nullptr)
		{
			int32 X = ItemComponent->GetSlotIndexX();
			int32 Y = ItemComponent->GetSlotIndexY();
			auto Key = TPair<int32, int32>(X, Y);

			if (DuplicationChecker.Contains(Key))
			{
				SLOW_LOG(Warning, TEXT("하위 컴포넌트 중 같은 인덱스를 가지는 컴포넌트(%s)를 발견했습니다."), *ItemComponent->GetName());
			}
			else
			{
				DuplicationChecker.Add(Key);
			}

			ItemComponents.Add(ItemComponent);
		}
	}

	// 슬롯에 아이템 컴포넌트를 추가합니다.
	for (auto& Item : ItemComponents)
	{
		int32 X = Item->GetSlotIndexX();
		int32 Y = Item->GetSlotIndexY();

		SetItemIndex(Item, X, Y);
	}
}

void ASokobanGameActor::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	Super::EndPlay(InEndPlayReason);
}

#if WITH_EDITOR

void ASokobanGameActor::PostEditChangeProperty(FPropertyChangedEvent& InEvent)
{
	Super::PostEditChangeProperty(InEvent);

	if (InEvent.MemberProperty == nullptr)
	{
		return;
	}

	FString PropertyName = InEvent.MemberProperty->GetNameCPP();

	if (PropertyName == nameof(ItemCountX) || PropertyName == nameof(ItemCountY))
	{
		OnPropertyChanged_ItemCount();
	}

	else RegisterPropertyChanged(SlotMesh)
	else RegisterPropertyChanged(SlotMeshScale)
}

#endif

void ASokobanGameActor::CheckSlotItem(USokobanGameItem* InItem) const
{
	CheckNull(InItem);

	int32 X = InItem->GetSlotIndexX();
	int32 Y = InItem->GetSlotIndexY();

	CHECK_ITEM_COUNT(X, 0, ItemCountX - 1);
	CHECK_ITEM_COUNT(Y, 0, ItemCountY - 1);
}

FVector2D ASokobanGameActor::QuerySlotLocation(int32 X, int32 Y) const
{
	CHECK_ITEM_COUNT(X, 0, ItemCountX - 1, FVector2D::ZeroVector);
	CHECK_ITEM_COUNT(Y, 0, ItemCountY - 1, FVector2D::ZeroVector);

	USokobanGameSlot* const& Slot = GetCell(X, Y);
	FVector RelativeLocation = Slot->GetRelativeLocation();

	return FVector2D(RelativeLocation.X, RelativeLocation.Y);
}

void ASokobanGameActor::OnPropertyChanged_ItemCount()
{
	CHECK_ITEM_COUNT(ItemCountX, 1, 20);
	CHECK_ITEM_COUNT(ItemCountY, 1, 20);

	// 기존 컴포넌트의 연결을 제거합니다.
	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		USokobanGameSlot* Slot = GetCell(X, Y);
		Slot->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}

	// 슬롯 컴포넌트를 추가합니다.
	SlotComponents.SetNum(ItemCountX * ItemCountY);
	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		USokobanGameSlot* Slot = NewCellComponent(X, Y);
		RefreshSlotItemProperty(Slot);
	}

	bRefreshed = true;
}

#if WITH_EDITOR

void ASokobanGameActor::OnPropertyChanged_SlotMesh()
{
	if (!bRefreshed)
	{
		OnPropertyChanged_ItemCount();
	}

	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		USokobanGameSlot* Slot = GetCell(X, Y);
		RefreshSlotItemProperty(Slot);
	}
}

void ASokobanGameActor::OnPropertyChanged_SlotMeshScale()
{
	if (!bRefreshed)
	{
		OnPropertyChanged_ItemCount();
	}

	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		USokobanGameSlot* Slot = GetCell(X, Y);
		RefreshSlotItemProperty(Slot);
	}
}

#endif

void ASokobanGameActor::RefreshSlotItemProperty(USokobanGameSlot* Item) const
{
	Item->SetStaticMesh(SlotMesh);
	Item->SetRelativeScale3D(SlotMeshScale);
}

auto ASokobanGameActor::NewCellComponent(int32 InX, int32 InY) -> USokobanGameSlot*
{
	FUObjectThreadContext& MyThreadContext = FUObjectThreadContext::Get();

	USokobanGameSlot* Component = nullptr;

	Component = NewObject<USokobanGameSlot>(this);
	Component->SetStaticMesh(SlotMesh);
	Component->SetRelativeLocation(FVector(CellWidth * (float)InX, CellHeight * (float)InY, 0.0f));
	Component->SetRelativeScale3D(SlotMeshScale);
	Component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Component->RegisterComponent();
	GetCell(InX, InY) = Component;

	return Component;
}

USokobanGameSlot*& ASokobanGameActor::GetCell(int32 InX, int32 InY)
{
	return SlotComponents[InY * ItemCountX + InX];
}

USokobanGameSlot* const& ASokobanGameActor::GetCell(int32 InX, int32 InY) const
{
	return SlotComponents[InY * ItemCountX + InX];
}

TTuple<int32, int32> ASokobanGameActor::Break(int32 Number) const
{
	return TTuple<int32, int32>(Number % ItemCountX, Number / ItemCountX);
}

void ASokobanGameActor::SetItemIndex(USokobanGameItem* InItem, int32 X, int32 Y)
{
	USokobanGameSlot* Slot = GetCell(X, Y);
	
	Slot->SetItem(InItem);
	InItem->SetSlotIndexX(X);
	InItem->SetSlotIndexY(Y);
}

#undef CHECK_ITEM_COUNT
#undef AssignIfValid
#undef RegisterPropertyChanged
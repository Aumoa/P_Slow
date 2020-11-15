// Copyright 2020 Team slow. All right reserved.

#include "Actor/SokobanGameActor.h"

#include "Common/SlowLogDefine.h"
#include "Common/SlowCommonMacros.h"
#include "Common/SlowCollisionProfile.h"
#include "Components/SokobanGameSlot.h"
#include "Components/SokobanGameItem.h"
#include "Components/SokobanGameMovableItem.h"
#include "Components/GoalIndicatorComponent.h"
#include "Controller/SlowPlayerController.h"

#define CHECK_ITEM_COUNT(XY, Min, Max, ...) \
if (XY < Min)\
{\
	UE_LOG(LogSlow, Log, TEXT("%s: %s의 값은 %d보다 크거나 같아야 합니다.(%d)"), __FUNCTIONT__, nameof(XY), Min, XY);\
	return __VA_ARGS__;\
}\
\
else if (XY > Max)\
{\
	UE_LOG(LogSlow, Log, TEXT("%s: %s의 값은 %d보다 작거나 같아야 합니다.(%d)"), __FUNCTIONT__, nameof(XY), Max, XY);\
	return __VA_ARGS__;\
}

#define CHECK_ITEM_INDEX(XY, Count, ...) CHECK_ITEM_COUNT(XY, 0, Count - 1, __VA_ARGS__)

#define RegisterPropertyChanged(VarName)\
if (PropertyName == nameof(VarName))\
{\
	OnPropertyChanged_##VarName();\
}

ASokobanGameActor::ASokobanGameActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bRefreshed = false;
	bSucceeded = false;

	ItemCountX = 10;
	ItemCountY = 10;
	MaxActionCount = 20;

	Root = CreateDefaultSubobject<UBoxComponent>(nameof(RootComponent));
	Root->SetMobility(EComponentMobility::Movable);
	SetRootComponent(Root);

	Root->SetCollisionProfileName(CollisionProfile::Trigger);

	SlotMesh = nullptr;
	CellWidth = 100.0f;
	CellHeight = 100.0f;
	SlotMeshScale = FVector(1.0f, 1.0f, 1.0f);

	RemainActionCount = 0;
}

void ASokobanGameActor::BeginPlay()
{
	Super::BeginPlay();

	Refresh();

	// 모든 하위 컴포넌트 중에서 USokobanGameItem 컴포넌트를 검색합니다.
	const TSet<UActorComponent*>& AllComponents = GetComponents();
	ItemComponents.Reserve(AllComponents.Num());

	TSet<TPair<int32, int32>> DuplicationChecker;
	for (auto& Item : AllComponents)
	{
		auto ItemComponent = Cast<USokobanGameItem>(Item);
		if (ItemComponent != nullptr)
		{
			int32 X = ItemComponent->ConstSlotIndexX;
			int32 Y = ItemComponent->ConstSlotIndexY;
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

	// 목적지 표시 컴포넌트를 생성합니다.
	if (GoalIndicatorClass != nullptr)
	{
		GoalIndicators.Reserve(GoalIndexes.Num());

		for (auto& Index : GoalIndexes)
		{
			auto [X, Y] = Index;

			UGoalIndicatorComponent* Component = NewObject<UGoalIndicatorComponent>(this, GoalIndicatorClass);
			Component->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
			Component->SetRelativeLocation(FVector(QuerySlotLocation(X, Y), 0.0f));
			Component->RegisterComponent();

			GoalIndicators.Add(Component);
		}
	}

	RemainActionCount = MaxActionCount;
	RefreshSlotReferences();
}

void ASokobanGameActor::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	Super::EndPlay(InEndPlayReason);
}

void ASokobanGameActor::Tick(float InDeltaSeconds)
{
	Super::Tick(InDeltaSeconds);

	bool bUpdating = false;
	for (auto& Item : ItemComponents)
	{
		if (Item->HasUpdating())
		{
			Item->CustomTick(InDeltaSeconds);
			bUpdating = true;
		}
	}

	if (!bUpdating)
	{
		ResolveTask();
	}
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

	else if (PropertyName == nameof(CellWidth) || PropertyName == nameof(CellHeight))
	{
		OnPropertyChanged_CellSize();
	}

	else RegisterPropertyChanged(SlotMesh)
	else RegisterPropertyChanged(SlotMeshScale)
}

#endif

bool ASokobanGameActor::MoveSlotItem(USokobanGameItem* InItem, int32 DestX, int32 DestY, bool bForceRetry)
{
	CHECK_ITEM_INDEX(DestX, ItemCountX, false);
	CHECK_ITEM_INDEX(DestY, ItemCountY, false);

	USokobanGameSlot& CurCell = *GetCell(DestX, DestY);
	if (CurCell.GetItem() != nullptr)
	{
		return false;
	}

	InItem->RemoveSlotReference();

	InItem->SlotIndexX = DestX;
	InItem->SlotIndexY = DestY;
	CurCell.SetItem(InItem);
	InItem->CurrentSlot = &CurCell;
	InItem->UpdateLocation();

	if (HasActorBegunPlay() && !bForceRetry)
	{
		ConsumeFlags CF = ConsumeMove();

		if (CheckGoals())
		{
			TaskQueue.Enqueue(Task_DestructAll);
			TaskQueue.Enqueue(Task_Succeeded);
		}
		else if (CF == CF_Countdown)
		{
			TaskQueue.Enqueue(Task_Destruct);
			TaskQueue.Enqueue(Task_Retry);
		}
	}

	return true;
}

FVector2D ASokobanGameActor::QuerySlotLocation(int32 X, int32 Y) const
{
	CHECK_ITEM_INDEX(X, ItemCountX, FVector2D::ZeroVector);
	CHECK_ITEM_INDEX(Y, ItemCountY, FVector2D::ZeroVector);

	int32 PivotX = ItemCountX / 2;
	int32 PivotY = ItemCountY / 2;

	FVector2D RelativeOffset = FVector2D((X - PivotX) * CellWidth, (Y - PivotY) * CellHeight);
	if ((ItemCountX % 2) == 0)
	{
		RelativeOffset.X += CellWidth * 0.5f;
	}
	if ((ItemCountY % 2) == 0)
	{
		RelativeOffset.Y += CellHeight * 0.5f;
	}
	return RelativeOffset;
}

bool ASokobanGameActor::CheckIndexMovable(int32 X, int32 Y) const
{
	CHECK_ITEM_INDEX(X, ItemCountX, false);
	CHECK_ITEM_INDEX(Y, ItemCountY, false);

	USokobanGameSlot* const& Slot = GetCell(X, Y);
	USokobanGameItem* SlotItem = Slot->GetItem();

	// 빈 공간으로만 이동할 수 있다.
	if (SlotItem == nullptr)
	{
		return true;
	}

	return false;
}

auto ASokobanGameActor::ConsumeMove() -> ConsumeFlags
{
	if (RemainActionCount <= 0)
	{
		return CF_Countdown;
	}

	RemainActionCount -= 1;
	return CF_Succeeded;
}

void ASokobanGameActor::Destruct()
{
	for (auto& Item : ItemComponents)
	{
		auto MovableItem = Cast<USokobanGameMovableItem>(Item);
		SafeInvoke(MovableItem).DestructItem();
	}
}

void ASokobanGameActor::DestructAll()
{
	for (auto& Item : ItemComponents)
	{
		SafeInvoke(Item).DestructItem();
	}
}

void ASokobanGameActor::Retry()
{
	SLOW_LOG(Verbose, TEXT("실패. 재시작."));

	for (auto& Item : ItemComponents)
	{
		SafeInvoke(Item).Retry();
	}

	RefreshSlotReferences();

	RemainActionCount = MaxActionCount;
}

void ASokobanGameActor::Succeeded()
{
	bSucceeded = true;
	SLOW_LOG(Verbose, TEXT("성공!"));

	for (auto& Item : ItemComponents)
	{
		Item->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		Item->DestroyComponent();
	}
}

void ASokobanGameActor::Refresh()
{
	OnPropertyChanged_ItemCount();
	OnPropertyChanged_SlotMesh();
	OnPropertyChanged_SlotMeshScale();
	OnPropertyChanged_CellSize();

	RefreshRootExtent();
}

#if WITH_EDITOR

void ASokobanGameActor::CreateAuto()
{
	auto SafeGet = [&](int32 Index) -> UClass*
	{
		if (ItemClass.Num() > Index)
		{
			return ItemClass[Index];
		}
		else
		{
			return nullptr;
		}
	};

	TArray<int32> SlotArray;
	SlotArray.SetNum(ItemCountX * ItemCountY);

	int32 NumChars = AutoGenerationText.Len();
	for (int32 i = 0; i < NumChars; ++i)
	{
		TCHAR SmallBuffer[2] = { 0, 0 };
		SmallBuffer[0] = AutoGenerationText[i];
		int32 Index = FCString::Atoi(SmallBuffer);
		SlotArray[i] = Index;
	}

	for (int32 i = 0; i < SlotArray.Num(); ++i)
	{
		UClass* CurClass = SafeGet(SlotArray[i]);
		if (CurClass != nullptr)
		{
			auto [X, Y] = Break(i);

			USokobanGameItem& ItemObject = *NewObject<USokobanGameItem>(this, CurClass);
			ItemObject.AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			ItemObject.RegisterComponent();

			MoveSlotItem(&ItemObject, X, Y);

			AutoGeneratedComponents.Add(&ItemObject);
		}
	}
}

void ASokobanGameActor::RemoveAllAutoGenerationComponents()
{
	for (int32 i = 0; i < AutoGeneratedComponents.Num(); ++i)
	{
		USokobanGameItem& Cur = *AutoGeneratedComponents[i];
		Cur.DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		Cur.RemoveSlotReference();
		Cur.ConditionalBeginDestroy();
	}

	AutoGeneratedComponents.SetNum(0);
}

void ASokobanGameActor::Cleanup()
{
	RemoveAllAutoGenerationComponents();

	for (auto& Slot : SlotComponents)
	{
		Slot->SetItem(nullptr);
	}
}

#endif

void ASokobanGameActor::OnPropertyChanged_ItemCount()
{
	CHECK_ITEM_COUNT(ItemCountX, 1, 20);
	CHECK_ITEM_COUNT(ItemCountY, 1, 20);

	auto SafeDispose = [](USokobanGameSlot*& Item)
	{
		if (Item != nullptr)
		{
			Item->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			Item->ConditionalBeginDestroy();
			Item = nullptr;
		}
	};

	// 기존 컴포넌트의 연결을 제거합니다.
	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		SafeDispose(GetCell(X, Y));
	}

	// 슬롯 컴포넌트를 추가합니다.
	SlotComponents.SetNum(ItemCountX * ItemCountY);
	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		NewCellComponent(X, Y);
		RefreshSlotItemProperty(X, Y);
	}

	RefreshRootExtent();

	bRefreshed = true;
}

void ASokobanGameActor::OnPropertyChanged_SlotMesh()
{
	if (!bRefreshed)
	{
		OnPropertyChanged_ItemCount();
	}

	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		RefreshSlotItemProperty(X, Y);
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
		RefreshSlotItemProperty(X, Y);
	}

	RefreshRootExtent();
}

void ASokobanGameActor::OnPropertyChanged_CellSize()
{
	if (!bRefreshed)
	{
		OnPropertyChanged_ItemCount();
	}

	for (int32 i = 0; i < SlotComponents.Num(); ++i)
	{
		auto [X, Y] = Break(i);
		RefreshSlotItemProperty(X, Y);
	}

	RefreshRootExtent();
}

void ASokobanGameActor::RefreshSlotItemProperty(int32 X, int32 Y) const
{
	USokobanGameSlot* Slot = GetCell(X, Y);

	Slot->SetStaticMesh(SlotMesh);
	Slot->SetRelativeScale3D(SlotMeshScale);
	Slot->SetRelativeLocation(FVector(QuerySlotLocation(X, Y), 0.0f));
}

auto ASokobanGameActor::NewCellComponent(int32 InX, int32 InY) -> USokobanGameSlot*
{
	UWorld* IsInWorldContext = GetWorld();

	USokobanGameSlot* Component = nullptr;

	Component = NewObject<USokobanGameSlot>(this);
	Component->SetStaticMesh(SlotMesh);
	Component->SetRelativeScale3D(SlotMeshScale);
	Component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	if (IsInWorldContext != nullptr)
	{
		Component->RegisterComponent();
	}

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

void ASokobanGameActor::ResolveTask()
{
	Tasks FirstTask = (Tasks)0;
	bool bDequeue = TaskQueue.Dequeue(FirstTask);

	if (bDequeue)
	{
		switch (FirstTask)
		{
		case Task_Destruct:
			Destruct();
			break;
		case Task_DestructAll:
			DestructAll();
			break;
		case Task_Retry:
			Retry();
			break;
		case Task_Succeeded:
			Succeeded();
			break;
		}
	}
}

void ASokobanGameActor::RefreshRootExtent()
{
	// 루트 컴포넌트의 크기를 변경합니다.
	int32 ExtentX = ItemCountX + 2;
	int32 ExtentY = ItemCountY + 2;
	Root->SetBoxExtent(FVector(CellWidth * ExtentX * 0.5f, CellHeight * ExtentY * 0.5f, SlotMeshScale.Z * 2.0f));
}

void ASokobanGameActor::RefreshSlotReferences()
{
	for (auto& Item : ItemComponents)
	{
		SafeInvoke(Item).RemoveSlotReference();
	}

	for (auto& Item : ItemComponents)
	{
		int32 X = Item->GetSlotIndexX();
		int32 Y = Item->GetSlotIndexY();

		USokobanGameSlot& Slot = *GetCell(X, Y);
		Slot.SetItem(Item);

		Item->CurrentSlot = &Slot;
	}
}

bool ASokobanGameActor::CheckGoals() const
{
	for (auto& i : GoalIndexes)
	{
		auto [X, Y] = i;
		USokobanGameSlot* const& Slot = GetCell(X, Y);
		if (Slot->GetItem() == nullptr)
		{
			return false;
		}
	}

	return true;
}

#undef CHECK_ITEM_COUNT
#undef CHECK_ITEN_INDEX
#undef RegisterPropertyChanged
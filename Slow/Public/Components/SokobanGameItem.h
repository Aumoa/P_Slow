﻿// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "IInteractionComponent.h"

#include "SokobanGameItem.generated.h"

class ASokobanGameActor;
class USokobanGameSlot;
enum ELevelTick;

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameItem : public UDestructibleComponent
{
	GENERATED_BODY()

private:
	mutable TWeakObjectPtr<ASokobanGameActor> MyActor;

	/** 슬롯 인덱스 X를 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexX;
	/** 슬롯 인덱스 Y를 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexY;

	int32 ConstSlotIndexX;
	int32 ConstSlotIndexY;

	USokobanGameSlot* CurrentSlot = nullptr;

protected:
	enum Direction
	{
		Dir_Forward,
		Dir_Right,
		Dir_Left,
		Dir_Back
	};

	FVector TwoDirection[2];

public:
	USokobanGameItem();

	void BeginPlay() override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;
#endif

	virtual void Retry();
	virtual void DestructItem();

	int32 GetSlotIndexX() const;
	void SetSlotIndexX(int32 InValue);
	int32 GetSlotIndexY() const;
	void SetSlotIndexY(int32 InValue);
	bool CanMoveAround() const;
	void SetCurrentSlot(USokobanGameSlot* InSlot);
	USokobanGameSlot* GetCurrentSlot() const;

protected:
	virtual void UpdateLocation(bool bForceMove = false);
	ASokobanGameActor* GetActor() const;

private:
	void UpdateSlot();

	template<class First, class Second>
	static FVector Select(const First& InFirstItem, int32 X, int32 Y, int32 Z, const Second& InSecondItem);
};
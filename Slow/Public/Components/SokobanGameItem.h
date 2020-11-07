// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SokobanGameItem.generated.h"

class ASokobanGameActor;
enum ELevelTick;

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameItem : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<ASokobanGameActor> MyActor;

	/** 슬롯 인덱스 X를 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexX;
	/** 슬롯 인덱스 Y를 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexY;
	/** 아이템이 초당 몇 cm을 이동하는지 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float InteropSpeed;

	FVector2D CurDestLocation;
	uint8 bMoving : 1;

public:
	USokobanGameItem();

	void BeginPlay() override;
	void TickComponent(float InDeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;
#endif

	int32 GetSlotIndexX() const;
	void SetSlotIndexX(int32 InValue);
	int32 GetSlotIndexY() const;
	void SetSlotIndexY(int32 InValue);
	
	bool IsMoving() const;

private:
	void UpdateSlot();

	template<class First, class Second>
	static FVector Select(const First& InFirstItem, int32 X, int32 Y, int32 Z, const Second& InSecondItem);
};
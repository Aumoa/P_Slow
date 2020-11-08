// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "IInteractionComponent.h"

#include "SokobanGameItem.generated.h"

class ASokobanGameActor;
enum ELevelTick;

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameItem : public UStaticMeshComponent, public IInteractionComponent
{
	GENERATED_BODY()

private:
	enum Direction
	{
		Dir_Forward,
		Dir_Right,
		Dir_Left,
		Dir_Back
	};

private:
	mutable TWeakObjectPtr<ASokobanGameActor> MyActor;

	/** 슬롯 인덱스 X를 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexX;
	/** 슬롯 인덱스 Y를 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexY;

	FVector TwoDirection[2];

	int32 ConstSlotIndexX;
	int32 ConstSlotIndexY;

public:
	USokobanGameItem();

	void BeginPlay() override;

	bool OnHitInteractionRay(AActor* InEventSender, FHitResult& InRemoteHitResult) override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;
#endif

	int32 GetSlotIndexX() const;
	void SetSlotIndexX(int32 InValue);
	int32 GetSlotIndexY() const;
	void SetSlotIndexY(int32 InValue);
	void Retry();

protected:
	virtual void UpdateLocation();
	ASokobanGameActor* GetActor() const;

private:
	void UpdateSlot();

	template<class First, class Second>
	static FVector Select(const First& InFirstItem, int32 X, int32 Y, int32 Z, const Second& InSecondItem);
};
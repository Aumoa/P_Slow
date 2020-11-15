// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SokobanGameItem.h"

#include "SokobanGameMovableItem.generated.h"

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameMovableItem : public USokobanGameItem, public IInteractionComponent
{
	GENERATED_BODY()

private:
	/** 아이템이 초당 몇 cm을 이동하는지 설정합니다. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float InteropSpeed;

	FVector2D CurDestLocation;
	uint8 bMoving : 1;
	uint8 bRetryRequest : 1;

public:
	USokobanGameMovableItem();

	void BeginPlay() override;
	void TickComponent(float InDeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

	bool OnHitInteractionRay(AActor* InEventSender, FHitResult& InRemoteHitResult) override;

	void Retry() override;

	bool IsMoving() const;

protected:
	void UpdateLocation(bool bForceMove) override;

private:
	template<class First, class Second>
	static FVector Select(const First& InFirstItem, int32 X, int32 Y, int32 Z, const Second& InSecondItem);
};
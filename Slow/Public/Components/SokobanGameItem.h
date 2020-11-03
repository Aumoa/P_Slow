// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "SokobanGameItem.generated.h"

UCLASS(ClassGroup = (SokobanGame), meta = (BlueprintSpawnableComponent))
class SLOW_API USokobanGameItem : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetSlotIndexX, BlueprintSetter = SetSlotIndexY, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexX;
	UPROPERTY(EditAnywhere, BlueprintGetter = GetSlotIndexY, BlueprintSetter = SetSlotIndexY, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndexY;

public:
	USokobanGameItem();

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;
#endif

	UFUNCTION(BlueprintGetter)
	int32 GetSlotIndexX() const;
	UFUNCTION(BlueprintSetter)
	void SetSlotIndexX(int32 InValue);
	UFUNCTION(BlueprintGetter)
	int32 GetSlotIndexY() const;
	UFUNCTION(BlueprintSetter)
	void SetSlotIndexY(int32 InValue);

private:
	void UpdateSlot();
};
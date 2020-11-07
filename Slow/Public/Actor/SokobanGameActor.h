﻿// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SokobanGameActor.generated.h"

class USokobanGameSlot;
class UStaticMesh;
class USokobanGameItem;

UCLASS()
class SLOW_API ASokobanGameActor : public AActor
{
	GENERATED_BODY()

private:
	uint8 bRefreshed : 1;

	UPROPERTY(EditAnywhere, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int32 ItemCountX;
	UPROPERTY(EditAnywhere, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int32 ItemCountY;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY()
	TArray<USokobanGameSlot*> SlotComponents;
	UPROPERTY()
	TArray<USokobanGameItem*> ItemComponents;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* SlotMesh;
	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	float CellWidth;
	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	float CellHeight;
	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	FVector SlotMeshScale;

public:
	ASokobanGameActor();

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;
#endif

	void CheckSlotItem(USokobanGameItem* InItem) const;
	FVector2D QuerySlotLocation(int32 X, int32 Y) const;

private:
	void OnPropertyChanged_ItemCount();
#if WITH_EDITOR
	void OnPropertyChanged_SlotMesh();
	void OnPropertyChanged_SlotMeshScale();
#endif
	void RefreshSlotItemProperty(USokobanGameSlot* Item) const;

	bool SafeComponentDispose(USokobanGameSlot*& InComponent);
	USokobanGameSlot* NewCellComponent(int32 InX, int32 InY);

	USokobanGameSlot*& GetCell(int32 InX, int32 InY);
	USokobanGameSlot* const& GetCell(int32 InX, int32 InY) const;
	TTuple<int32, int32> Break(int32 Number) const;

	void SetItemIndex(USokobanGameItem* InItem, int32 X, int32 Y);
};
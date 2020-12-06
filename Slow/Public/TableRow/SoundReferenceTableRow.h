// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "SoundReferenceTableRow.generated.h"

USTRUCT(BlueprintType)
struct FSoundReferenceTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	/** 이 사운드가 재생되기까지 지연 시간을 설정합니다. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayedTiming;

	/** 재생될 사운드 레퍼런스를 설정합니다. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoundReference;

	/** 볼륨 배수를 설정합니다. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float VolumeMultiplier;

	/** 피치 배수를 설정합니다. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PitchMultiplier;

	/** 사운드가 재생되는 동안 사운드 액터가 출처를 따라갑니다. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bFollow : 1;

	/** 사운드 액터가 붙을 스켈레탈 소켓 이름을 설정합니다. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AttachName;

	FSoundReferenceTableRow();
};
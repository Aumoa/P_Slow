// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "AnimNotify_PlaySoundReferenced.generated.h"

UCLASS(hidecategories = "AnimNotify", meta = (DisplayName = "Slow Play Sound"))
class SLOW_API UAnimNotify_PlaySoundReferenced : public UAnimNotify_PlaySound
{
	GENERATED_BODY()

private:
	UDataTable* AnimBasedSoundReferences;

	UPROPERTY(EditAnywhere)
	FName ReferenceKey;

public:
	UAnimNotify_PlaySoundReferenced();

	void Notify(USkeletalMeshComponent* InMeshComponent, UAnimSequenceBase* InAnimation);
};
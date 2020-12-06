// Copyright 2020 Team slow. All right reserved.

#include "AnimNotify/AnimNotify_PlaySoundReferenced.h"

#include "Common/SlowCommonMacros.h"
#include "TableRow/SoundReferenceTableRow.h"
#include "Controller/SlowPlayerController.h"

UAnimNotify_PlaySoundReferenced::UAnimNotify_PlaySoundReferenced()
	: AnimBasedSoundReferences(nullptr)
{
	static FString AssetReference = TEXT("/Game/Slow/Datatable/Sounds/DT_AnimBasedSoundReference.DT_AnimBasedSoundReference");
	static ConstructorHelpers::FObjectFinder<UDataTable> Table(*AssetReference);

	if (!Table.Succeeded())
	{
		SLOW_LOG(Error, TEXT("Cannot found datatable in \"%s\"."), *AssetReference);
		return;
	}

	AnimBasedSoundReferences = Table.Object;
}

void UAnimNotify_PlaySoundReferenced::Notify(USkeletalMeshComponent* InMeshComponent, UAnimSequenceBase* InAnimation)
{
	if (AnimBasedSoundReferences == nullptr)
	{
		SLOW_LOG(Error, TEXT("Datatable is not loaded."));
		return;
	}

	auto It = AnimBasedSoundReferences->FindRow<FSoundReferenceTableRow>(ReferenceKey, TEXT(""));
	if (It == nullptr)
	{
		SLOW_LOG(Error, TEXT("Cannot found reference key[%s] in table[%s]."), *ReferenceKey.ToString(), *AnimBasedSoundReferences->GetName());
		return;
	}

	Sound = It->SoundReference.LoadSynchronous();
	VolumeMultiplier = It->VolumeMultiplier;
	PitchMultiplier = It->PitchMultiplier;
	bFollow = It->bFollow;
	AttachName = It->AttachName;

	if (It->DelayedTiming < 0.001f)
	{
		Super::Notify(InMeshComponent, InAnimation);
	}
	else
	{
		auto PC = Cast<ASlowPlayerController>(UGameplayStatics::GetPlayerController(InMeshComponent, 0));
		if (PC == nullptr)
		{
			SLOW_LOG(Error, TEXT("Cannot use delayed timing notify."));
			return;
		}

		ASlowPlayerController::FGameThreadActionDelegateArgs Args;
		Args.Sender = this;
		Args.Args = nullptr;
		Args.DelayedInvoke = It->DelayedTiming;

		PC->EnqueueGameThreadAction([&](UObject* Sender, UObject* InArgs)
			{
				Super::Notify(InMeshComponent, InAnimation);
			}
		, Args);
	}
}
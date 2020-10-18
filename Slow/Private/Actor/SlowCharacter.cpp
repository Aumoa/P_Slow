// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowCharacter.h"

#include "LogDefine.h"

ASlowCharacter::ASlowCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanAnimErrorLog = true;

	CombatTag.bCanTarget = true;
}

void ASlowCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASlowCharacter::SetCombatTag(const FCombatTag& InCombatTag)
{
	CombatTag = InCombatTag;
}

FCombatTag ASlowCharacter::GetCombatTag() const
{
	return CombatTag;
}

USlowAnimInstance* ASlowCharacter::GetAnimInstance() const
{
	if (!SlowAnimInstance.IsValid())
	{
		QueryAnimInstance();
		if (bCanAnimErrorLog && !SlowAnimInstance.IsValid())
		{
			UE_LOG(LogSlow, Error, TEXT("ASlowCharacter::GetAnimInstance(): 애니메이션 인스턴스를 불러오는데 실패하였습니다. 이 로그는 한 번만 출력됩니다."));
			bCanAnimErrorLog = false;
		}
	}

	return SlowAnimInstance.Get();
}

void ASlowCharacter::QueryAnimInstance() const
{
	USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (SkeletalMesh == nullptr)
	{
		UE_LOG(LogSlow, Error, TEXT("ASlowCharacter::QueryAnimInstance(): 스켈레탈 메시가 설정되지 않았습니다."));
		return;
	}

	UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		UE_LOG(LogSlow, Error, TEXT("ASlowCharacter::QueryAnimInstance(): 스켈레탈 메시에 애니메이션이 설정되지 않았습니다."));
		return;
	}

	SlowAnimInstance = Cast<USlowAnimInstance>(AnimInstance);
}
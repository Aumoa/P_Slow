// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowStatBasedCharacter.h"

#include "Components/Behavior.h"
#include "Effect/StatModifyLinearEffect.h"

void ASlowStatBasedCharacter::BeginPlay()
{
	Super::BeginPlay();

	StatValidCheck();
	AttrInstance.HealthPoint = InitialAttribute.StartHealth;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s HP : %d / %d"), *this->GetName(), AttrInstance.HealthPoint >= 0 ? AttrInstance.HealthPoint : 0, InitialAttribute.MaxHealth));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s HP : %d / %d"), *this->GetName(), AttrInstance.HealthPoint >= 0 ? AttrInstance.HealthPoint : 0, InitialAttribute.MaxHealth));
}

ASlowStatBasedCharacter::ASlowStatBasedCharacter()
{
	
}

void ASlowStatBasedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FEquipments ASlowStatBasedCharacter::GetCurrentEquipments() const
{
	return FEquipments();
}

FBaseAttributeConfig ASlowStatBasedCharacter::GetInitialAttribute() const
{
	return InitialAttribute;
}

void ASlowStatBasedCharacter::ApplyEffect(const FStatModifyLinearEffect& InEffect)
{
	//
	// 어트리뷰트는 Set 함수가 제공되지 않습니다.
	// 외부에서 어트리뷰트를 직접 변경하기 위해서 GetCurrentAttributes() 함수로 조회한 후
	// 적절한 값의 이펙트를 생성하여야 합니다.

	FAttrInstance InModifyValue = InEffect.GetModifyValue();

	AttrInstance.HealthPoint -= InModifyValue.HealthPoint;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s HP : %d / %d"), *this->GetName(),AttrInstance.HealthPoint >= 0 ? AttrInstance.HealthPoint : 0, InitialAttribute.MaxHealth));
	StatValidCheck();
}

FAttrInstance ASlowStatBasedCharacter::GetCurrentAttributes() const
{
	return AttrInstance;
}

bool ASlowStatBasedCharacter::Attack()
{
	return false;
}

void ASlowStatBasedCharacter::SetInitialAttribute(const FBaseAttributeConfig& InInitialAttribute)
{
	InitialAttribute = InInitialAttribute;
	StatValidCheck();
}

void ASlowStatBasedCharacter::OnActorKill()
{
	// 기본 행동은 이 액터를 게임 월드에서 파괴하는 것입니다.
	Destroy();
}

void ASlowStatBasedCharacter::StatValidCheck()
{
	// HP 스탯에 대한 변경 사항을 검사합니다.
	if (AttrInstance.HealthPoint < InitialAttribute.MinHealth)
	{
		OnActorKill();
	}
	else if (AttrInstance.HealthPoint >= InitialAttribute.MaxHealth)
	{
		AttrInstance.HealthPoint = InitialAttribute.MaxHealth;
	}
}
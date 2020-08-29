// Copyright 2020 Team slow. All right reserved.

#include "Components/StatComponent.h"

#include "LogDefine.h"
#include "Structures/RelativeDamage.h"
#include "Attributes/AttributeInstance.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	attributeInstance = CreateDefaultSubobject<UAttributeInstance>(TEXT("AttributeInstance"));
}

void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	attributeInstance->BeginPlay(baseAttribute);
}

void UStatComponent::ApplyDamage(const FRelativeDamage& relativeDamage)
{
	attributeInstance->ApplyDamage(relativeDamage);
}
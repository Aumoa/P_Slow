// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/SlowCharacter.h"

#include "Attributes/BaseAttributeConfig.h"
#include "Attributes/AttrInstance.h"

#include "SlowStatBasedCharacter.generated.h"

struct FAttrInstance;

UCLASS()
class SLOW_API ASlowStatBasedCharacter : public ASlowCharacter
{
	GENERATED_BODY()

private:
	FAttrInstance AttrInstance;

	uint8 bBeginPlay : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FBaseAttributeConfig InitialAttribute;

protected:
	void BeginPlay() override;

public:
	ASlowStatBasedCharacter();

	void Tick(float DeltaTime) override;

	void SetInitialAttribute(const FBaseAttributeConfig& InInitialAttribute);
	FBaseAttributeConfig GetInitialAttribute() const;
};
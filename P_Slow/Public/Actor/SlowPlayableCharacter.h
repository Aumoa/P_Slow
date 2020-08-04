// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Actor/SlowCharacter.h"

#include "SlowPlayableCharacter.generated.h"

class UInputComponent;
class APlayerController;

UCLASS()
class P_SLOW_API ASlowPlayableCharacter : public ASlowCharacter
{
	GENERATED_BODY()

public:
	ASlowPlayableCharacter();

protected:
	void BeginPlay() override;

public:
	void Tick( float DeltaTime ) override;
	void OnActionInput( const FName& ActionName, bool bPressed );

protected:
	UPROPERTY( BlueprintReadWrite ) bool bCanMove;

private:
	void OnMouseAction( bool bPressed );
	FVector2D GetCurrentMouseScreenPos( APlayerController* PlayerController ) const;
};

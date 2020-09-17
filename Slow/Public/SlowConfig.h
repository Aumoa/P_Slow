// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Scene/SceneBase.h"
#include "Ability/WeaponBase.h"
#include "Actor/SlowPlayableCharacter.h"

#include "SlowConfig.generated.h"

UCLASS( Blueprintable )
class SLOW_API USlowConfig : public UObject
{
	GENERATED_BODY()

public:
	USlowConfig( const FObjectInitializer& Initializer );
	
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "General" ) FString EntryPoint;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "General" ) bool bSkipDemo;

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Scene" ) TSubclassOf<USceneBase> StartupScene;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Scene" ) TSubclassOf<USceneBase> DemoScene;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Scene" ) TSubclassOf<USceneBase> IntroScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf <UWeaponBase> HatchetWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf <UWeaponBase> SwordWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf <UWeaponBase> HammerWeapon;
};

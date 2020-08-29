// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Scene/SceneBase.h"
#include "IntroScene.generated.h"

UCLASS()
class SLOW_API UIntroScene : public USceneBase
{
	GENERATED_BODY()
	
public:
	void BeginPlay( UObject* Args = nullptr ) override;
	void EndPlay() override;

	void OnActionInput( const FName& ActionName, bool bPressed );

private:
	void OnIntroNextSceneInput( bool bPressed );
};

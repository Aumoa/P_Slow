// Copyright 2020. Team slow, All right reserved.


#include "Manager/SpawnManager.h"

#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "SlowPlayableCharacterState.h"
#include "LogDefine.h"

#include "Actor/SlowPlayableCharacter.h"

#include "Kismet/GameplayStatics.h"

void USpawnManager::Initialize( UObject* This )
{

}

ASlowPlayableCharacter* USpawnManager::SpawnPlayerPawn( UObject* This, const FTransform& Transform )
{
	UE_LOG( LogSlow, Log, TEXT( "USpawnManager::SpawnPlayerPawn()" ) );

	auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( This ) );
	auto World = This->GetWorld();

	return World->SpawnActor<ASlowPlayableCharacter>( GameInstance->Config->PlayableCharacter, Transform );
}
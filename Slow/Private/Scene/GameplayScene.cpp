// Copyright 2020 Team slow. All right reserved.


#include "Scene/GameplayScene.h"

#include "GameFramework/GameStateBase.h"

#include "LogDefine.h"
#include "SlowGameInstance.h"
#include "SlowConfig.h"
#include "SlowPlayableCharacterState.h"

#include "Actor/SlowPlayerState.h"

#include "Kismet/GameplayStatics.h"

void UGameplayScene::BeginPlay( UObject* Args )
{
	UGameplayStatics::OpenLevel( this, TEXT( "Gameplay" ) );

	NextStreamingLevel = TEXT( "Gameplay_Lobby" );

	ReadyPlayerCharacter();
}

void UGameplayScene::EndPlay()
{

}

void UGameplayScene::ReadyPlayerCharacter()
{
	auto GameState = GetWorld()->GetGameState();
	auto PlayerState = Cast<ASlowPlayerState>( GameState->PlayerArray[0] );

	if ( PlayerState->PC == nullptr )
	{
		auto GameInstance = Cast<USlowGameInstance>( UGameplayStatics::GetGameInstance( this ) );
		auto Config = GameInstance->GetConfig();

		// Empty playable character.
		PlayerState->PC = NewObject<USlowPlayableCharacterState>( this );
	}
}
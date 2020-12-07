// Copyright 2020 Team slow. All right reserved.

#include "Components/CheatConsoleComponent.h"

#include "SlowGameInstance.h"
#include "Common/SlowCommonMacros.h"
#include "Manager/SceneManager.h"
#include "Manager/SpawnManager.h"
#include "Scene/GameplayLobbyScene.h"
#include "Actor/SlowPlayableCharacter.h"

#define MakeCheat(CheatName) else if (Splits[0].ToLower() == FString(#CheatName).ToLower())

UCheatConsoleComponent::UCheatConsoleComponent()
{

}

bool UCheatConsoleComponent::ConsoleCommand(const FString& CheatString, bool bWriteToLog)
{
	TArray<FString> Splits;
	CheatString.ParseIntoArray(Splits, TEXT(" "), true);

	TFunction<void(int32)> IndexOutOfRangeLogger = [&](int32 Index)
	{
		SLOW_LOG(Warning, TEXT("Index[%d] is out of range."), Index);
	};

	FString DefaultArgStr = TEXT("");
	int32 DefaultArgInt = 0;
	float DefaultArgFloat = 0;
	bool bIndexOutOfRange = false;

	auto ArgsAsString = [&](int32 Index) -> FString
	{
		if (Index >= Splits.Num() - 1)
		{
			IndexOutOfRangeLogger(Index);
			bIndexOutOfRange = true;
			return DefaultArgStr;
		}

		return Splits[Index + 1];
	};

	auto ArgsAsInt = [&](int32 Index)
	{
		if (Index >= Splits.Num() - 1)
		{
			IndexOutOfRangeLogger(Index);
			bIndexOutOfRange = true;
			return DefaultArgInt;
		}

		return FCString::Atoi(*Splits[Index + 1]);
	};

	auto ArgsAsFloat = [&](int32 Index)
	{
		if (Index >= Splits.Num() - 1)
		{
			IndexOutOfRangeLogger(Index);
			bIndexOutOfRange = true;
			return DefaultArgFloat;
		}

		return FCString::Atof(*Splits[Index + 1]);
	};

	auto CheatFailedHandle = [](const TCHAR* Message)
	{
		SLOW_LOG(Warning, TEXT("Cheat failed with follow reason: %s"), Message);
	};

	if (Splits.Num() == 0)
	{
		return false;
	}

	MakeCheat(ReloadLevel)
	{
		auto GameplayScene = Cast<UGameplayLobbyScene>(SCENE_MANAGER.GetCurrentScene());
		if (GameplayScene == nullptr)
		{
			CheatFailedHandle(TEXT("Current scene is not type of GameplayLobbyScene."));
			return true;
		}

		GameplayScene->ReloadLevels();
	}

	MakeCheat(MigrateLevelGroup)
	{
		auto GameplayScene = Cast<UGameplayLobbyScene>(SCENE_MANAGER.GetCurrentScene());
		if (GameplayScene == nullptr)
		{
			CheatFailedHandle(TEXT("Current scene is not type of GameplayLobbyScene."));
			return true;
		}

		GameplayScene->MigrateLevelGroup(*ArgsAsString(0));
	}

	MakeCheat(Goto)
	{
		IndexOutOfRangeLogger = [&](int32 Index)
		{
			SLOW_LOG(Warning, TEXT("Goto cheat need three arguments."));
		};

		ASlowPlayableCharacter* PlayerPawn = SPAWN_MANAGER.GetPlayerPawn();
		if (PlayerPawn != nullptr)
		{
			FTransform CurrTransform = PlayerPawn->GetActorTransform();
			CurrTransform.SetLocation(FVector(ArgsAsFloat(0), ArgsAsFloat(1), ArgsAsFloat(2)));
			if (!bIndexOutOfRange)
			{
				PlayerPawn->SetActorTransform(CurrTransform);
			}
		}
	}

	else
	{
		return false;
	}

	return true;
}
// Copyright 2020 Aumoa.lib. All right reserved.

#include "Components/CheatConsoleComponent.h"

#include "SlowGameInstance.h"
#include "Common/SlowCommonMacros.h"
#include "Manager/SceneManager.h"
#include "Scene/GameplayLobbyScene.h"

#define MakeCheat(CheatName) else if (Splits[0] == FString(#CheatName))

UCheatConsoleComponent::UCheatConsoleComponent()
{

}

bool UCheatConsoleComponent::ConsoleCommand(const FString& CheatString, bool bWriteToLog)
{
	TArray<FString> Splits;
	CheatString.ParseIntoArray(Splits, TEXT(" "), true);

	auto ArgsAsString = [&](int32 Index) -> FString
	{
		if (Index >= Splits.Num())
		{
			SLOW_LOG(Error, TEXT("Index[%d] is out of range."), Index);
			return TEXT("");
		}

		return Splits[Index + 1];
	};

	auto ArgsAsInt = [&](int32 Index)
	{
		FString Str = ArgsAsString(Index);
		return FCString::Atoi(*Str);
	};

	auto ArgsAsFloat = [&](int32 Index)
	{
		FString Str = ArgsAsString(Index);
		return FCString::Atof(*Str);
	};

	auto CheatFailedHandle = [](const TCHAR* Message)
	{
		SLOW_LOG(Warning, TEXT("Cheat failed with follow reason: %s"), Message);
	};

	if (Splits.Num() == 0)
	{
		return false;
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

	else
	{
		return false;
	}

	return true;
}
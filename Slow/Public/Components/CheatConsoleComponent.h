﻿

#pragma once

#include "CheatConsoleComponent.generated.h"

UCLASS()
class SLOW_API UCheatConsoleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCheatConsoleComponent();

	bool ConsoleCommand(const FString& CheatString, bool bWriteToLog);
};
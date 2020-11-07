// Copyright 2020 Team slow. All right reserved.

#include "Common/SlowConsoleVar.h"

namespace ConsoleVariable::Slow
{
	TAutoConsoleVariable<bool> SkipDemo(TEXT("Slow.SkipDemo"), false, TEXT("Skip demo scene."), 0);
}
// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/ScopeLock.h"

template<class T>
inline const char* __nameof__(const T&, const char* xx)
{
	return xx;
}

template<class T>
inline const char* __nameof__(const char* xx)
{
	return xx;
}

#define ScopedLock(x) FScopeLock lock_##x(x.Get())
#define __FUNCTIONT__ *FString(__FUNCTION__)
#define nameof(x) *FString(__nameof__(x, #x))
#define nameof_c(x) *FString(__nameof__<x>(#x))
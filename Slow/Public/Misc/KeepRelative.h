// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "CoreMinimal.h"

template<class T>
class TKeepRelative
{
	T Origin;
	T Relative;

public:
	TKeepRelative()
		: Origin{ }
		, Relative{ }
	{

	}

	CONSTEXPR TKeepRelative(const T& InInitialValue)
		: Origin(InInitialValue)
		, Relative{ }
	{

	}

	CONSTEXPR TKeepRelative(const T& InOrigin, const T& InRelative)
		: Origin(InOrigin)
		, Relative(InRelative)
	{

	}

	CONSTEXPR TKeepRelative(T&& InInitialValue)
		: Origin(MoveTemp(InitialValue))
		, Relative{ }
	{

	}

	CONSTEXPR TKeepRelative(T&& InOrigin, T&& InRelative)
		: Origin(MoveTemp(InOrigin))
		, Relative(MoveTemp(InRelative))
	{

	}

	CONSTEXPR TKeepRelative(const TKeepRelative& InCopy)
		: Origin(InCopy.Origin)
		, Relative(InCopy.Realtive)
	{

	}

	CONSTEXPR TKeepRelative(TKeepRelative&& InMove)
		: Origin(MoveTemp(InMove.Origin))
		, Relative(MoveTemp(InMove.Relative))
	{

	}

	TKeepRelative& SetOrigin(const T& InValue)
	{
		Origin = InValue;
		return *this;
	}

	TKeepRelative& SetOrigin(T&& InValue)
	{
		Origin = MoveTemp(InValue);
		return *this;
	}

	TKeepRelative& SetRelative(const T& InValue)
	{
		Relative = InValue;
		return *this;
	}

	TKeepRelative& SetRelative(T&& InValue)
	{
		Relative = MoveTemp(InValue);
		return *this;
	}

	CONSTEXPR T GetOrigin() const
	{
		return Origin;
	}

	CONSTEXPR T GetRelative() const
	{
		return Relative;
	}

	CONSTEXPR T GetValue() const
	{
		return Origin + Relative;
	}

	CONSTEXPR bool operator ==(const TKeepRelative& InRight) const
	{
		return GetValue() == InRight.GetValue();
	}

	CONSTEXPR bool operator !=(const TKeepRelative& InRight) const
	{
		return GetValue() != InRight.GetValue();
	}

	CONSTEXPR TKeepRelative operator +(const T& InValue) const
	{
		return TKeepRelative(Origin, InValue);
	}

	TKeepRelative& operator =(const T& InValue)
	{
		Origin = InValue;
		return *this;
	}

	TKeepRelative& operator =(T&& InValue)
	{
		Origin = MoveTemp(InValue);
		return *this;
	}

	TKeepRelative& operator +=(const T& InValue)
	{
		Relative = InValue;
		return *this;
	}

	TKeepRelative& operator +=(T&& InValue)
	{
		Relative = MoveTemp(InValue);
		return *this;
	}
};
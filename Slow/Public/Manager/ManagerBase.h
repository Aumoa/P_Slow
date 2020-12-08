// Copyright 2020 Team slow. All right reserved.

#pragma once

#include "ManagerBase.generated.h"

class USlowGameInstance;

UCLASS()
class SLOW_API UManagerBase : public UObject
{
	GENERATED_BODY()

private:
	static USlowGameInstance* GameInstance;

protected:
	template< class T, typename TEnableIf<TIsDerivedFrom<T, UManagerBase>::Value>::Type* = nullptr >
	static T* GetSingletonInstance()
	{
		return Cast<T>( GetSingletonInstanceInternal( T::StaticClass() ) );
	}

public:
	virtual void Initialize(USlowGameInstance* GInstance);

	static USlowGameInstance* GetGameInstance();

private:
	static UObject* GetSingletonInstanceInternal( TSubclassOf<UManagerBase> ClassType );
};
// Copyright 2020 Team slow. All right reserved.

#include "Manager/ConfigManager.h"

#include "Common/SlowCommonMacros.h"
#include "SlowConfig.h"

UConfigManager* UConfigManager::SingletonInstance = nullptr;

UConfigManager::UConfigManager()
	: SoftClassReference(nullptr)
	, Config(nullptr)
{
	static FString ConfigReferencePath = TEXT("Blueprint'/Game/Slow/Blueprints/Embedded/BP_SlowConfig.BP_SlowConfig_C'");
	static ConstructorHelpers::FObjectFinder<UObject> BP_SlowConfigFinder(*ConfigReferencePath);

	if (!BP_SlowConfigFinder.Succeeded())
	{
		SLOW_LOG(Error, TEXT("Cannot found blueprint config asset as follow path: \"%s\"."), *ConfigReferencePath);
		return;
	}

	SoftClassReference = BP_SlowConfigFinder.Object->GetClass();
}

void UConfigManager::Initialize(USlowGameInstance* GInstance)
{
	Super::Initialize(GInstance);

	UClass* ClassReference = SoftClassReference;
	if (ClassReference == nullptr)
	{
		SLOW_LOG(Error, TEXT("Class reference of config blueprint is not loaded. Create as default."));
		ClassReference = USlowConfig::StaticClass();
	}

	Config = NewObject<USlowConfig>(ClassReference);
	if (Config == nullptr)
	{
		SLOW_LOG(Error, TEXT("Class reference is not a %s type. Create as default."), nameof_c(USlowConfig));
		Config = NewObject<USlowConfig>(USlowConfig::StaticClass());
	}

	SingletonInstance = this;
}

USlowConfig* UConfigManager::GetBlueprintConfig() const
{
	return Config;
}

UConfigManager* UConfigManager::GetInstance()
{
	return SingletonInstance;
}
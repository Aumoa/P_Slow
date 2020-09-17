// Copyright 2020 Team slow. All right reserved.


#include "SlowConfig.h"

#include "Scene/StartupScene.h"
#include "Scene/DemoScene.h"
#include "Scene/IntroScene.h"

#include "Ability/HatchetWeapon.h"
#include "Ability/SwordWeapon.h"
#include "Ability/HammerWeapon.h"

USlowConfig::USlowConfig( const FObjectInitializer& Initializer ) : Super( Initializer )
{
	EntryPoint = TEXT( "Startup" );
	bSkipDemo = false;

	StartupScene = UStartupScene::StaticClass();
	DemoScene = UDemoScene::StaticClass();
	IntroScene = UIntroScene::StaticClass();

	HatchetWeapon = UHatchetWeapon::StaticClass();
	SwordWeapon = USwordWeapon::StaticClass();
	HammerWeapon = UHammerWeapon::StaticClass();
}
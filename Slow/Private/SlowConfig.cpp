// Copyright 2020 Team slow. All right reserved.


#include "SlowConfig.h"

#include "Scene/StartupScene.h"
#include "Scene/DemoScene.h"
#include "Scene/IntroScene.h"

USlowConfig::USlowConfig( const FObjectInitializer& Initializer ) : Super( Initializer )
{
	EntryPoint = TEXT( "Startup" );
	bSkipDemo = false;

	StartupScene = UStartupScene::StaticClass();
	DemoScene = UDemoScene::StaticClass();
	IntroScene = UIntroScene::StaticClass();
}
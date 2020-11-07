// Copyright 2020 Team slow. All right reserved.

#include "Components/SokobanGameMovableItem.h"

USokobanGameMovableItem::USokobanGameMovableItem()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultCubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (DefaultCubeMesh.Succeeded())
	{
		SetStaticMesh(DefaultCubeMesh.Object);
	}
}
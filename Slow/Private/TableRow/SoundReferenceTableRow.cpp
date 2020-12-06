// Copyright 2020 Team slow. All right reserved.

#include "TableRow/SoundReferenceTableRow.h"

FSoundReferenceTableRow::FSoundReferenceTableRow()
{
	DelayedTiming = 0;
	SoundReference = nullptr;
	VolumeMultiplier = 1.0f;
	PitchMultiplier = 1.0f;
	bFollow = true;
	AttachName = NAME_None;
}
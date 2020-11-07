// Copyright 2020 Team slow. All right reserved.

#pragma once



class UWeaponBase;

/// <summary>
/// 캐릭터가 착용할 수 있는 장비에 대한 레퍼런스입니다.
/// </summary>
struct FEquipments
{
	/// <summary>
	/// 착용한 장비를 나타냅니다.
	/// </summary>
	TWeakObjectPtr<UWeaponBase> Weapon;

	FEquipments();
};
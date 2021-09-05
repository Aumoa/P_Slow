// Copyright 2020. Team slow, All right reserved.

#include "Ability/SwordWeapon.h"
#include "Manager/WeaponManager.h"
#include "Datatable/WeaponReference.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Requirement/CostRequirement.h"
#include "Requirement/CooldownRequirement.h"
#include "Components/Behavior.h"
#include "Effect/StatModifyLinearEffect.h"
#include "Actor/SlowStatBasedCharacter.h"
#include "Ability/AttackAbility.h"

USwordWeapon::USwordWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_W(TEXT("StaticMesh'/Game/Slow/Meshes/Weapon/Sword/SM_WeaponSword.SM_WeaponSword'"));
	StaticMesh_Weapon = SM_W.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Attack_Sword.MTG_PC_Attack_Sword'"));
	AttackMontage = Attack_MTG.Object;

	Collision_Weapon = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision_Weapon"));
	Collision_Weapon->SetCapsuleHalfHeight(70);
	Collision_Weapon->SetCapsuleRadius(6.6f);
	Collision_Weapon->SetRelativeLocation(FVector(0, -2, -15));
}



void USwordWeapon::BeginWeapon(AActor* Owner)
{
	//Effect 클래스에서 Caster를 생성자로 받기 때문에 소유하고 있는 AActor 클래스를 가져온다.
	MyOwner = Owner;

	//해당 무기가 장착될 소켓 이름
	SocketName = TEXT("SwordSocket");

	//"Sword"에 해당하는 레퍼런스를 데이터테이블에서 받는다. 
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Sword"));
	
	//무기의 사용 제약 조건을 받는다.
	//내구도 제약 조건을 추가한다.
	TSharedPtr<FCostRequirement> Cost_Weapon = MakeShared<FCostRequirement>();
	Cost_Weapon->SetupUsageCount(WeaponReferenceTable->MaxUsageCount);

	//쿨타임 제약 조건을 추가한다.
	TSharedPtr<FCooldownRequirement> Cooldown_Weapon = MakeShared<FCooldownRequirement>();
	Cooldown_Weapon->SetupCooldown(WeaponReferenceTable->SwapCoolDown);


	//무기의 사용 제약 조건을 Array에 추가한다.
	Requirements_Weapon.Add(Cost_Weapon);
	Requirements_Weapon.Add(Cooldown_Weapon);

	//데이터테이블의 해당 무기 데미지 정보를 기반으로 Effect클래스를 생성한다.
	//Effect 클래스는 상대방에게 보낼 효과를 담고 있다.
	FAttrInstance MondifyValue = {};
	MondifyValue.AttackDamage = WeaponReferenceTable->Damage;

	FStatModifyLinearEffect* DamageEffect = new FStatModifyLinearEffect(MyOwner, MondifyValue);


	//대상에게 전달할 효과 정보를 담고 있는 Array에 DamageEffect를 추가한다.
	WeaponEffectList.Add(DamageEffect);

	ComboList.Empty();
	ComboList.Emplace(TEXT("Sword_Combo1"));
	ComboList.Emplace(TEXT("Sword_Combo2"));
	ComboList.Emplace(TEXT("Sword_Combo3"));

	//무기 소유자의 공격 어빌리티를 가져온다.
	ASlowStatBasedCharacter* SlowCharacter = Cast<ASlowStatBasedCharacter>(Owner);
	if (SlowCharacter)
	{
		AttackAbility = SlowCharacter->GetFAttackAbility();
	}

	//공격 시도 시 발동하는 효과와 공격 성공 시 발동하는 효과를 AttackAbility에 등록한다.
	AddAttackImmediateEffect();
	AddAttackHitEffect();
}

//무기 사용 종료 시, 호출된다.
void USwordWeapon::EndWeapon()
{
	AttackAbility->FAttackImmediateEffect.Clear();
	AttackAbility->FAttackHitEffect.Clear();
}

//무기의 모든 제약 조건을 가져온다.
TArray<TSharedPtr<FRequirementBase>> USwordWeapon::GetAllRequirements() const
{
	return Requirements_Weapon;
}

//공격 시도 시, 대리자에게 발동할 함수를 추가한다.
void USwordWeapon::AddAttackImmediateEffect()
{
	if (!AttackAbility)
	{
		return;
	}

	//대리자에게 공격 내구도 감소 효과를 추가한다.
	AttackAbility->FAttackImmediateEffect.AddUFunction(this, FName("ConsumeWeaponCost"));
}

//공격 적중 시, 대리자에게 발동할 함수를 추가한다.
void USwordWeapon::AddAttackHitEffect()
{
	if (!AttackAbility)
	{
		return;
	}
}

//무기 내구도를 1감소 시킨다.
void USwordWeapon::ConsumeWeaponCost()
{
	for (TSharedPtr<FRequirementBase> Requirement : Requirements_Weapon)
	{
		//TshardPtr은 Dynamic Cast를 지원하지 않기 때문에 Static Cast를 사용한다.
		TSharedPtr<FCostRequirement> CostRequirement = StaticCastSharedPtr<FCostRequirement>(Requirement);

		//주의점: Static Cast이므로 FCooldownRequirement도 IsValid된다. CostRequirement의 생성자가 호출됬는지 확인한다.
		if (CostRequirement.IsValid())
		{
			CostRequirement->Consume(1);
		}
	}
}

bool USwordWeapon::SwapConditionInternal()
{

	return true;
}

TSubclassOf<UBehavior> USwordWeapon::GetEffect() const
{
	return UBehavior::StaticClass();
}

UStaticMesh* USwordWeapon::GetWeaponMesh()
{
	return StaticMesh_Weapon;
}

FName USwordWeapon::GetSocketName()
{
	return SocketName;
}

int USwordWeapon::GetMaxComboCount()
{
	return ComboList.Num();
}

UAnimMontage* USwordWeapon::GetAttackMontage()
{
	if (AttackMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HammerWeapon, AttackMontage is Nullptr."));
	}

	return AttackMontage;
}

TArray<FName> USwordWeapon::GetComboList()
{
	return ComboList;
}

UCapsuleComponent* USwordWeapon::GetCapsuleComponent()
{
	return Collision_Weapon;
}

FWeaponReferenceTableRow* USwordWeapon::GetWeaponDataTableRow()
{
	return WeaponReferenceTable;
}


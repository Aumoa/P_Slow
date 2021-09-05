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
	//Effect Ŭ�������� Caster�� �����ڷ� �ޱ� ������ �����ϰ� �ִ� AActor Ŭ������ �����´�.
	MyOwner = Owner;

	//�ش� ���Ⱑ ������ ���� �̸�
	SocketName = TEXT("SwordSocket");

	//"Sword"�� �ش��ϴ� ���۷����� ���������̺��� �޴´�. 
	WeaponReferenceTable = UWeaponReference::GetReferenceTableRow(TEXT("Sword"));
	
	//������ ��� ���� ������ �޴´�.
	//������ ���� ������ �߰��Ѵ�.
	TSharedPtr<FCostRequirement> Cost_Weapon = MakeShared<FCostRequirement>();
	Cost_Weapon->SetupUsageCount(WeaponReferenceTable->MaxUsageCount);

	//��Ÿ�� ���� ������ �߰��Ѵ�.
	TSharedPtr<FCooldownRequirement> Cooldown_Weapon = MakeShared<FCooldownRequirement>();
	Cooldown_Weapon->SetupCooldown(WeaponReferenceTable->SwapCoolDown);


	//������ ��� ���� ������ Array�� �߰��Ѵ�.
	Requirements_Weapon.Add(Cost_Weapon);
	Requirements_Weapon.Add(Cooldown_Weapon);

	//���������̺��� �ش� ���� ������ ������ ������� EffectŬ������ �����Ѵ�.
	//Effect Ŭ������ ���濡�� ���� ȿ���� ��� �ִ�.
	FAttrInstance MondifyValue = {};
	MondifyValue.AttackDamage = WeaponReferenceTable->Damage;

	FStatModifyLinearEffect* DamageEffect = new FStatModifyLinearEffect(MyOwner, MondifyValue);


	//��󿡰� ������ ȿ�� ������ ��� �ִ� Array�� DamageEffect�� �߰��Ѵ�.
	WeaponEffectList.Add(DamageEffect);

	ComboList.Empty();
	ComboList.Emplace(TEXT("Sword_Combo1"));
	ComboList.Emplace(TEXT("Sword_Combo2"));
	ComboList.Emplace(TEXT("Sword_Combo3"));

	//���� �������� ���� �����Ƽ�� �����´�.
	ASlowStatBasedCharacter* SlowCharacter = Cast<ASlowStatBasedCharacter>(Owner);
	if (SlowCharacter)
	{
		AttackAbility = SlowCharacter->GetFAttackAbility();
	}

	//���� �õ� �� �ߵ��ϴ� ȿ���� ���� ���� �� �ߵ��ϴ� ȿ���� AttackAbility�� ����Ѵ�.
	AddAttackImmediateEffect();
	AddAttackHitEffect();
}

//���� ��� ���� ��, ȣ��ȴ�.
void USwordWeapon::EndWeapon()
{
	AttackAbility->FAttackImmediateEffect.Clear();
	AttackAbility->FAttackHitEffect.Clear();
}

//������ ��� ���� ������ �����´�.
TArray<TSharedPtr<FRequirementBase>> USwordWeapon::GetAllRequirements() const
{
	return Requirements_Weapon;
}

//���� �õ� ��, �븮�ڿ��� �ߵ��� �Լ��� �߰��Ѵ�.
void USwordWeapon::AddAttackImmediateEffect()
{
	if (!AttackAbility)
	{
		return;
	}

	//�븮�ڿ��� ���� ������ ���� ȿ���� �߰��Ѵ�.
	AttackAbility->FAttackImmediateEffect.AddUFunction(this, FName("ConsumeWeaponCost"));
}

//���� ���� ��, �븮�ڿ��� �ߵ��� �Լ��� �߰��Ѵ�.
void USwordWeapon::AddAttackHitEffect()
{
	if (!AttackAbility)
	{
		return;
	}
}

//���� �������� 1���� ��Ų��.
void USwordWeapon::ConsumeWeaponCost()
{
	for (TSharedPtr<FRequirementBase> Requirement : Requirements_Weapon)
	{
		//TshardPtr�� Dynamic Cast�� �������� �ʱ� ������ Static Cast�� ����Ѵ�.
		TSharedPtr<FCostRequirement> CostRequirement = StaticCastSharedPtr<FCostRequirement>(Requirement);

		//������: Static Cast�̹Ƿ� FCooldownRequirement�� IsValid�ȴ�. CostRequirement�� �����ڰ� ȣ������ Ȯ���Ѵ�.
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


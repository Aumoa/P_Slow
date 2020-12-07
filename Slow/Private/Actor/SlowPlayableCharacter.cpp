// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowPlayableCharacter.h"

#include "Common/SlowLogDefine.h"
#include "Common/SlowInputDefine.h"
#include "Common/SlowTraceChannels.h"
#include "Common/SlowCommonMacros.h"
#include "Ability/AbilityBase.h"
#include "Ability/MoveAbility.h"
#include "Ability/AttackAbility.h"
#include "Ability/ILocationTargetAbility.h"
#include "Manager/WeaponManager.h"
#include "AnimInstance/SlowAnimInstance.h"
#include "Components/IInteractionComponent.h"
#include "Effect/ActorEffect.h"
#include "Effect/StatModifyLinearEffect.h"
#include "Attributes/AttrInstance.h"
#include "TableRow/WeaponReferenceTableRow.h"
#include "Manager/WidgetManager.h"
#include "UI/Widget/SlowCombatUIWidget.h"
#include "Scene/GameplayLobbyScene.h"
#include "Manager/SceneManager.h"

ASlowPlayableCharacter::ASlowPlayableCharacter()
{	
	IsFindInteractionObject = false;
	RollInput = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	Collision_Weapon = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision_Weapon"));
	Collision_Weapon->OnComponentBeginOverlap.AddDynamic(this, &ASlowPlayableCharacter::OnWeaponCollisionBeginOverlap);
	Collision_Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Roll_MTG(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Roll.MTG_PC_Roll'"));
	RollMontage = Roll_MTG.Object;

	static ConstructorHelpers::FClassFinder<UCameraShake> CS_LoadCoustom(TEXT("/Game/Slow/Blueprints/Components/BP_PlayerAttackCameraShake"));
	if (CS_LoadCoustom.Succeeded())
	{
		CS_PlayerAttack = CS_LoadCoustom.Class;
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("CS_PlayerAttack : %s "), *CS_PlayerAttack->GetName());

	HurtMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Hurt_Ham.MTG_PC_Hurt_Ham'")).Object);
	HurtMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Hurt_Sw.MTG_PC_Hurt_Sw'")).Object);
	HurtMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Hurt_Hat.MTG_PC_Hurt_Hat'")).Object);
	HurtMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/PC/MTG_PC_Faint.MTG_PC_Faint'")).Object);

	NewSpringArm();
}

ASlowPlayableCharacter::~ASlowPlayableCharacter()
{

}

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveAbility = MakeShared<FMoveAbility>();
	AttackAbility = MakeShared<FAttackAbility>();
	//Weapon = NewObject<UStaticMeshComponent>(this);

	MouseActionSlot.SetAbility(MoveAbility.Get());
	MouseSelectionSlot.SetAbility(AttackAbility.Get());

	IsAttack = false;
	IsOverlapAttack = false;
	ComboCount = 0;
	
	SetControlMode(0);

	NewWeaponManager();
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("HammerSocket"));
	Collision_Weapon->AttachToComponent(Weapon, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	AnimInstance = GetMesh()->GetAnimInstance();

	DamageEffect = new FStatModifyLinearEffect(this);

	MyCombatUIWidget = UWidgetManager::CreateSlowWidget<USlowCombatUIWidget>(TEXT("Widget.SlowCombatUI"));
	MyCombatUIWidget->SetOwnerCharacter(this);

	PlayerDirection = GetActorForwardVector();
	RollTime = -1.0f;
	BehaviorCoolDown = 0.0f;
	AttackCooldown = 0.0f;
	MoveCooldown = 0.0f;
	
	PlayerKill_ZPos = GetActorLocation().Z - 7000;

}

void ASlowPlayableCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0)
	{
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		//SpringArm->bDoCollisionTest = true;
		//bUseControllerRotationYaw = true;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		//GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}

void ASlowPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RollTime > 0.0f)
	{
		RollTime -= DeltaTime;
		LaunchCharacter(PlayerDirection * 180000 * DeltaTime, true, true);
	}

	if (AttackCooldown > 0.0f && BehaviorCoolDown <= 0.0f)
	{
		AttackCooldown -= DeltaTime;
	}

	if (MoveCooldown > 0.0f && BehaviorCoolDown <= 0.0f)
	{
		MoveCooldown -= DeltaTime;
	}


	if (BehaviorCoolDown > 0.0f)
	{
		BehaviorCoolDown -= DeltaTime;
	}

	if (GetActorLocation().Z <= PlayerKill_ZPos)
	{
		OnActorKill();
	}

	//UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::Tick :: AttackCoolDown : %f "), AttackCooldown);
	//UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::Tick :: MoveCoolDown : %f "), MoveCooldown);
	//UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::Tick :: BehaviorCoolDown : %f "), BehaviorCoolDown);
	
}




void ASlowPlayableCharacter::OnActionInput(const FName& ActionName, bool bPressed)
{
	if (ActionName == IA_PeaceMode && IsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::OnActionInput :: Reset Init!!"));
		USceneManager::SwitchScene(USceneManager::GetCurrentScene());
		return;
	}


	if (BehaviorCoolDown > 0.0f)
	{
		return;
	}
	
	if (ActionName == IA_MouseAction)
	{
		OnMouseAction(bPressed);
	}

	if (ActionName == IA_MouseSelection)
	{
		OnMouseSelection(bPressed);
	}

	else if (ActionName == IA_WeaponSwap)
	{
		if (WeaponManager != nullptr)
		{
			WeaponManager->NextWeapon();
			Equipment.Weapon = WeaponManager->GetCurrentWeapon();
			SetWeaponSocketName();
			SetWeaponMesh();
			SetWeaponData();

			
			//Collision_Weapon->AttachToComponent(Weapon, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}

	else if (ActionName == IA_Interaction)
	{
		
		IsFindInteractionObject = true;

		FireInteractionRay();
	}

	else if (ActionName == IA_Roll)
	{

		if (AttrInstance.StaminaPoint < RollCost)
		{
			return;
		}

		OnPlayerAttackMontageEnd();
		AnimInstance->StopAllMontages(0.01f);
		AnimInstance->Montage_Play(RollMontage);
		RollInput = true;

		PlayerDirection = GetPlayerDirection();

		RollTime = 0.4f;
		AttrInstance.StaminaPoint -= RollCost;
		BehaviorCoolDown = 0.5f;


		
		
		//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		//Direction*=300.0f;
		//GetMesh()->AddImpulseAtLocation(GetVelocity() * 300.0f, GetActorLocation());
	}
	
	else if (ActionName == IA_Jump)
	{
		bPressedJump = true;
	}

	else if (ActionName == IA_PeaceMode)
	{
		WeaponManager->SetPeaceMode();
		DisableWeapon();
	}
}

void ASlowPlayableCharacter::OnMouseAction(bool bPressed)
{
	if (bPressed)
	{
		auto PlayerController = Cast<APlayerController>(Controller);

		FHitResult HitResult;
		bool bHit = PlayerController->GetHitResultUnderCursor(ECC_AcceptMouseAction, false, HitResult);

		if (bHit) {
			TSharedPtr<FAbilityBase> ability = MouseActionSlot.GetAbility().Pin();
			if (!ability.IsValid()) {
				return;
			}

			auto targetBasedAbility = dynamic_cast<ILocationTargetAbility*>(ability.Get());
			if (targetBasedAbility == nullptr) {
				return;
			}

			targetBasedAbility->ExecuteIndirect(this);
			targetBasedAbility->SetTarget(HitResult.Location);
		}
	}
}

void ASlowPlayableCharacter::OnMouseSelection(bool bPressed)
{
	if (AttackCooldown + BehaviorCoolDown > 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::OnMouseSelection :: Is AttackCoolDown"));
		return;
	}

	if (bPressed)
	{
		UE_LOG(LogTemp, Warning, TEXT("IsAttack :: %s"), IsAttack == true ? TEXT("True") : TEXT("False"));
		if (IsAttack == false)
		{
			ComboCount = 0;
			OnPlayerAttack();
		}

		else
		{
			IsOverlapAttack = true;
		}
	}

	else
	{
		
	}
}

void ASlowPlayableCharacter::OnPlayerAttack()
{
	if (AnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AnimInstance! :: ASlowPlayableCharacter -> OnPlayerAttack()"));
		return;
	}
		
	else if (AttackMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Attack Montage! :: ASlowPlayableCharacter -> OnPlayerAttack()"));
		return;
	}
		
	else if (ComboList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ComboList. :: ASlowPlayableCharacter -> OnPlayerAttack()"));
		return;
	}

	else if (Equipment.Weapon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Equipment.Weapon. :: ASlowPlayableCharacter -> OnPlayerAttack()"));
		return;
	}

	/*else if (AnimInstance->Montage_IsPlaying(RollMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("RollMontage Is Playing. Try after. :: ASlowPlayableCharacter -> OnPlayerAttack()"));
		return;
	}*/

	else
	{
		IsAttack = true;
		IsValidAttack = true;
		MoveCooldown = 0.2f;

		PlayerDirection = GetPlayerDirection();
		LaunchCharacter(PlayerDirection * 1000, true, true);

		AnimInstance->StopAllMontages(0.15f);
		AnimInstance->Montage_Play(AttackMontage);

		if (!(AnimInstance->Montage_IsPlaying(AttackMontage)))
		{

		}

		else
		{
			AnimInstance->Montage_JumpToSection(ComboList[ComboCount],AttackMontage);
		}
	}
}

void ASlowPlayableCharacter::OnPlayerAttackEnd()
{
	IsAttack = false;

	if(ComboCount+1 == MaxComboCount)
		ComboCount = 0;

	if(Collision_Weapon != nullptr)
		Collision_Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}

void ASlowPlayableCharacter::OnAttackInputChecking()	
{
	if (IsOverlapAttack)
	{
		ComboCount = (ComboCount+1) % MaxComboCount;

		IsOverlapAttack = false;
		OnColStartAttack();
		OnPlayerAttack();
	}
}

void ASlowPlayableCharacter::OnColStartAttack()
{
	if(Collision_Weapon != nullptr)
		Collision_Weapon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ASlowPlayableCharacter::OnPlayerAttackMontageEnd()
{
	IsAttack = false;

	ComboCount = 0;

	if (Collision_Weapon != nullptr)
		Collision_Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASlowPlayableCharacter::OnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlowStatBasedCharacter *OtherCharacter = Cast<ASlowStatBasedCharacter>(OtherActor);

	if (OtherCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::OnWeaponCollisionBeginOverlap :: Error(OtherCharacter is null)"));
		return;
	}
		
	
	if (OtherActor == this)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::OnWeaponCollisionBeginOverlap :: Error(OtherActor is null)"));
		return;
	}
		
	
	if (IsValidAttack == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowPlayableCharacter::OnWeaponCollisionBeginOverlap :: Error(IsValideAttack is false)"));
		return;
	}
		

	AttackAbility->SetTarget(OtherCharacter);
	AttackAbility->ExecuteIndirect(this);
	MyCombatUIWidget->SetTarget(OtherCharacter);

	DamageEffect->Apply(OtherCharacter);

	IsValidAttack = false;
	Collision_Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	float CameraShakeScale = 1.f;

	if (MyCombatUIWidget->GetBossFaint_Percent() < 0.0f)
	{
		CameraShakeScale = 2.5f;
	}
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CS_PlayerAttack,1.0f* CameraShakeScale);

	UE_LOG(LogTemp, Warning, TEXT("Collision BeginOverlap :: %s"), *OtherActor->GetName());
}

void ASlowPlayableCharacter::NewWeaponManager()
{
	WeaponManager = NewObject<UWeaponManager>(this);
	WeaponManager->Init();
	
}

void ASlowPlayableCharacter::NewSpringArm()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-88.0f),FRotator(0.0f,-90.0f,0.0f));
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f,0.0f,0.0f));
}



#pragma region Axis Input Function
void ASlowPlayableCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(AX_MoveForward, this, &ASlowPlayableCharacter::OnMoveForward);
	InputComponent->BindAxis(AX_MoveRight, this, &ASlowPlayableCharacter::OnMoveRight);
	InputComponent->BindAxis(AX_Turn, this, &ASlowPlayableCharacter::AddYawInput);
	InputComponent->BindAxis(AX_LookUp, this, &ASlowPlayableCharacter::AddPitchInput);

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent Called"));
}

FEquipments ASlowPlayableCharacter::GetCurrentEquipments() const
{
	return Equipment;
}


void ASlowPlayableCharacter::OnMoveForward(float NewAxisValue)
{
	/*if (NewAxisValue == 0.0f)
	{
		return;
	}
	*/
	if (MoveCooldown + BehaviorCoolDown > 0.0f)
	{
		return;
	}

	/*if (AnimInstance->IsAnyMontagePlaying())
	{
		return;
	}*/

	

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();
	AddMovementInput(Direction, NewAxisValue);
	

	/*FRotator rotation = FRotator(0, 0, GetControlRotation().Roll);
	FVector forward = FQuat(rotation).GetForwardVector();

	AddMovementInput(forward, NewAxisValue);*/

	
}

void ASlowPlayableCharacter::OnMoveRight(float NewAxisValue)
{
	/*
	if (NewAxisValue == 0.0f)
	{
		return;
	}
	*/
	if (MoveCooldown + BehaviorCoolDown > 0.0f)
	{
		return;
	}

	/*if (AnimInstance->IsAnyMontagePlaying())
	{
		return;
	}*/


	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::Y);
	
	Direction.Z = 0.0f;
	Direction.Normalize();
	AddMovementInput(Direction, NewAxisValue);

	/*FRotator rotation = FRotator(0, 0, GetControlRotation().Roll);
	FVector right = FQuat(rotation).GetRightVector();

	AddMovementInput(right, NewAxisValue);*/


}

void ASlowPlayableCharacter::AddYawInput(float NewAxisValue)
{
	if(NewAxisValue == 0.0f) 
	{
		return;
	}

	if (IsDead)
	{
		return;
	}
	
	AddControllerYawInput(NewAxisValue);
}

void ASlowPlayableCharacter::AddPitchInput(float NewAxisValue)
{

	if (NewAxisValue == 0.0f)
	{
		return;
	}

	if (IsDead)
	{
		return;
	}

	AddControllerPitchInput(NewAxisValue);
}
FVector ASlowPlayableCharacter::GetPlayerDirection()
{
	FVector	Direction = GetActorForwardVector();
	Direction.Z = 0.0f;
	Direction.Normalize();

	return Direction;
}
#pragma endregion


#pragma region Internal Data Get/Set
int ASlowPlayableCharacter::GetCurrentWeaponNum()
{
	if (WeaponManager != nullptr)
	{
		return WeaponManager->GetWeaponNum();
	}

	return -1;
}

bool ASlowPlayableCharacter::GetSwapAinmState()
{
	if (WeaponManager != nullptr)
	{
		return WeaponManager->GetSwapAnimState();
	}

	return false;
}

bool ASlowPlayableCharacter::GetIsFindInteractionObject()
{
	if (IsFindInteractionObject)
	{
		IsFindInteractionObject = false;
		return true;
	}

	return false;
}
bool ASlowPlayableCharacter::GetRollAnimState()
{
	if (RollInput)
	{
		RollInput = false;
		return true;
	}

	else
	{
		return false;
	}
}

bool ASlowPlayableCharacter::GetIsBattle()
{
	if (WeaponManager != nullptr)
	{
		return WeaponManager->GetIsBattle();
	}

	return false;
}

bool ASlowPlayableCharacter::GetIsDead() const
{
	return IsDead;
}


void ASlowPlayableCharacter::SetWeaponMesh()
{
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		UE_LOG(LogTemp, Warning, TEXT("SetWeaponMesh Init."));
		UStaticMesh* WeaponMeshObject = WeaponManager->GetWeaponMeshObject();

		if (WeaponMeshObject != nullptr)
		{
			Weapon->SetStaticMesh(WeaponMeshObject);
			UE_LOG(LogTemp, Warning, TEXT("WeaponMeshObject is StaticMesh."));
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WeaponMeshObject is Nullptr."));
		}
		//Weapon->SetupAttachment(GetMesh(), WeaponSocket);
		//Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,WeaponSocket);
		//Weapon->AttachTo(GetMesh(),WeaponSocket);
	}

}

void ASlowPlayableCharacter::SetWeaponSocketName()
{
	/*if (WeaponManager != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponManager is Sculptress."));
		return;
	}*/

	WeaponSocket = WeaponManager->GetSocketName();
	UE_LOG(LogTemp, Warning, TEXT("SetSocket :: SetSocketName :: %s"), *WeaponSocket.ToString());
}

void ASlowPlayableCharacter::SetWeaponData()
{
	AttackMontage = WeaponManager->GetAttackMontage();
	ComboList = WeaponManager->GetComboList();
	MaxComboCount = WeaponManager->GetMaxComboCount();

	Weapon->Activate();
	Collision_Weapon->Activate();

	FAttrInstance AttrData_Weapon;
	AttrData_Weapon.HealthPoint = WeaponManager->GetWeaponDataTable()->Damage;
	DamageEffect->SetModifyValue(AttrData_Weapon);

	//무기 콜리전 세팅
	UCapsuleComponent* Collision_WeaponData = WeaponManager->GetCapsuleComponent();
	Collision_Weapon->SetRelativeLocationAndRotation(Collision_WeaponData->GetRelativeLocation(),
		Collision_WeaponData->GetRelativeRotation());
	Collision_Weapon->SetCapsuleHalfHeight(Collision_WeaponData->GetUnscaledCapsuleHalfHeight());
	Collision_Weapon->SetCapsuleRadius(Collision_WeaponData->GetUnscaledCapsuleRadius());
	Collision_Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
}

void ASlowPlayableCharacter::DisableWeapon()
{
	Weapon->SetStaticMesh(nullptr);
	AttackMontage = nullptr;
	ComboList.Empty();
	MaxComboCount = 0;

	FAttrInstance AttrData_Weapon;
	AttrData_Weapon.HealthPoint = 0;
	DamageEffect->SetModifyValue(AttrData_Weapon);

	Equipment.Weapon = nullptr;

	Weapon->Deactivate();
	Collision_Weapon->Deactivate();
	
	//AnimInstance->StopAllMontages(0.1f);
}


#pragma endregion

bool ASlowPlayableCharacter::FireInteractionRay(float RayLength)
{
	const FVector MyLocation = GetActorLocation();
	const FVector ForwardDir = GetActorRotation().RotateVector(FVector::ForwardVector);

	const FVector RayStart = MyLocation;
	const FVector RayEnd = MyLocation + ForwardDir * RayLength;

	UWorld* const World = GetWorld();
	if (World == nullptr)
	{
		SLOW_LOG(Error, TEXT("게임이 시작되지 않았거나 액터가 올바른 World 컨텍스트가 아닙니다."));
		return false;
	}

	FHitResult HitResult;
	FCollisionQueryParams QueryParams(TEXT("Interaction"), false, this);
	bool bHit = World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Interaction, QueryParams);
	if (!bHit)
	{
		return false;
	}

	UPrimitiveComponent* HitComponent = HitResult.Component.Get();
	if (HitComponent == nullptr)
	{
		return false;
	}

	IInteractionComponent* InteractionComponent = Cast<IInteractionComponent>(HitComponent);
	if (InteractionComponent == nullptr)
	{
		return false;
	}

	return InteractionComponent->OnHitInteractionRay(this, HitResult);
}

bool ASlowPlayableCharacter::AddFaint(float num)
{
	if (num <= 0.0f)
	{
		return false;
	}

	if(BehaviorCoolDown < num)
		BehaviorCoolDown = num;

	if (IsDead)
	{
		return false;
	}

	int WeaponNum = GetCurrentWeaponNum();

	OnPlayerAttackMontageEnd();

	AnimInstance->StopAllMontages(0.01f);

	if (WeaponNum == -1)
	{
		AnimInstance->Montage_Play(HurtMontages[HurtMontages.Num() - 1]); //평화 상태라면 배열 가장 마지막 애니메이션 출력
		return true;
	}

	if (!HurtMontages.IsValidIndex(WeaponNum))
	{
		return false;
	}

	AnimInstance->Montage_Play(HurtMontages[WeaponNum]);

	return true;
}

float ASlowPlayableCharacter::GetBehaviorCoolDown() const
{
	return BehaviorCoolDown;
}

void ASlowPlayableCharacter::SetBehaviorCoolDown(float num)
{	
	BehaviorCoolDown = num;
}

void ASlowPlayableCharacter::OnActorKill()
{
	if (IsDead)
	{
		return;
	}

	BehaviorCoolDown = 99999.0f;
	IsDead = true;
	UWidgetManager::CreateSlowWidget<USlowWidgetBase>(TEXT("Widget.SlowDeathLogoUI"));
}

ASlowStatBasedCharacter* ASlowPlayableCharacter::GetTarget()
{
	if (AttackAbility == nullptr)
	{
		return nullptr;
	}

	ASlowStatBasedCharacter *Character = Cast<ASlowStatBasedCharacter>(AttackAbility->GetTarget());

	return Character;
}

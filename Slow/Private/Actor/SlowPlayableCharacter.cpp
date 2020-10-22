// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowPlayableCharacter.h"

#include "SlowTraceChannels.h"
#include "LogDefine.h"
#include "SlowInputDefine.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Ability/AbilityBase.h"
#include "Ability/MoveAbility.h"
#include "Ability/ILocationTargetAbility.h"
#include "Manager/WeaponManager.h"
#include "AnimInstance/SlowAnimInstance.h"

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveAbility = MakeShared<FMoveAbility>();
	
	NewWeaponManager();

	//Weapon = NewObject<UStaticMeshComponent>(this);

	MouseActionSlot.SetAbility(MoveAbility.Get());

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
}

ASlowPlayableCharacter::ASlowPlayableCharacter()
{
	WeaponSocket = TEXT("WeaponPoint");

	IsFindInteractionObject = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));	
	
}

ASlowPlayableCharacter::~ASlowPlayableCharacter()
{

}

void ASlowPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlowPlayableCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(AX_Turn, this, &ASlowPlayableCharacter::AddYawInput);
	InputComponent->BindAxis(AX_LookUp, this, &ASlowPlayableCharacter::AddPitchInput);
	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent Called"));
}

void ASlowPlayableCharacter::OnActionInput(const FName& ActionName, bool bPressed)
{

	if (ActionName == IA_MouseAction)
	{
		OnMouseAction(bPressed);
	}

	else if (ActionName == IA_WeaponSwap)
	{
		if (WeaponManager != nullptr)
		{
			WeaponManager->NextWeapon();
			SetWeaponMesh();
		}
	}

	else if (ActionName == IA_Interaction)
	{
		//트레이스로 상호작용 물체 체크
		IsFindInteractionObject = true;
	}

	else if (ActionName == IA_Roll)
	{
		
	}
}

void ASlowPlayableCharacter::AddYawInput(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void ASlowPlayableCharacter::AddPitchInput(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
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

void ASlowPlayableCharacter::NewWeaponManager()
{
	WeaponManager = NewObject<UWeaponManager>(this);
	WeaponManager->Init();
	UE_LOG(LogTemp,Warning,TEXT("New WeaponManager()"));
}



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

void ASlowPlayableCharacter::SetWeaponMesh()
{
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{

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


#pragma endregion


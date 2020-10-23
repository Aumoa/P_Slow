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
#include "GameFramework/Actor.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

void ASlowPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveAbility = MakeShared<FMoveAbility>();
	
	NewWeaponManager();

	//Weapon = NewObject<UStaticMeshComponent>(this);

	MouseActionSlot.SetAbility(MoveAbility.Get());

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);

	
	SetControlMode(0);
}

void ASlowPlayableCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0)
	{
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bDoCollisionTest = true;
		//bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}

ASlowPlayableCharacter::ASlowPlayableCharacter()
{
	WeaponSocket = TEXT("WeaponPoint");

	IsFindInteractionObject = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));	
	
	NewSpringArm();
}

ASlowPlayableCharacter::~ASlowPlayableCharacter()
{
	
}

void ASlowPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	
	else if (ActionName == IA_Jump)
	{

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

void ASlowPlayableCharacter::NewWeaponManager()
{
	WeaponManager = NewObject<UWeaponManager>(this);
	WeaponManager->Init();
	UE_LOG(LogTemp,Warning,TEXT("New WeaponManager()"));
}

void ASlowPlayableCharacter::NewSpringArm()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-88.0f),FRotator(0.0f,-90.0f,0.0f));
	SpringArm->TargetArmLength = 400.0f;
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

void ASlowPlayableCharacter::OnMoveForward(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)
	{
		return;
	}

	

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, NewAxisValue);

	/*
	FRotator rotation = FRotator(0, 0, GetControlRotation().Roll);
	FVector forward = FQuat(rotation).GetForwardVector();

	AddMovementInput(forward, NewAxisValue);
	*/
	
}

void ASlowPlayableCharacter::OnMoveRight(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)
	{
		return;
	}

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, NewAxisValue);

	/*
	FRotator rotation = FRotator(0, 0, GetControlRotation().Roll);
	FVector right = FQuat(rotation).GetRightVector();

	AddMovementInput(right, NewAxisValue);
	*/
	
}

void ASlowPlayableCharacter::AddYawInput(float NewAxisValue)
{
	if(NewAxisValue == 0.0f) 
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

	AddControllerPitchInput(NewAxisValue);
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


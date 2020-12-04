// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowMobCharacterBase.h"
#include "Controller/SlowMobController.h"
#include "Effect/StatModifyLinearEffect.h"

ASlowMobCharacterBase::ASlowMobCharacterBase()
{
	AIControllerClass = ASlowMobController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttackSocketName = TEXT("AttackSocket");

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	AttackCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollision"));
	
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ASlowMobCharacterBase::OnHitCollisionBeginOverlap);
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AttackCollision->RegisterComponent();
	AddInstanceComponent(AttackCollision);

	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_FourWayAttack.MTG_Boss1_FourWayAttack'")).Object);
	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_ComboAttack.MTG_Boss1_ComboAttack'")).Object);
	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_spinningAttack.MTG_Boss1_SpinningAttack'")).Object);
	
	
}

void ASlowMobCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttackSocketName);
	AttackCollision->AttachToComponent(Weapon, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//AttackCollision->SetRelativeRotation(FRotator(0,90,0));

	DamageEffect = new FStatModifyLinearEffect(this);
	FAttrInstance DamageEffectAttr;
	DamageEffectAttr.HealthPoint = InitialAttribute.DefaultDamage;
	DamageEffect->SetModifyValue(DamageEffectAttr);

	
}

void ASlowMobCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

bool ASlowMobCharacterBase::Monster_Attack()
{
	if (AttackCollision == nullptr)
	{
		return false;
	}

	IsAttack = true;
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	/*DrawDebugBox(GetWorld(), AttackCollision->GetComponentLocation(), AttackCollision->GetScaledBoxExtent(),
		AttackCollision->GetComponentRotation().Quaternion(),FColor::Yellow, false, 2.2f, 0, 5);*/
	return true;
}

void ASlowMobCharacterBase::Monster_AttackEnd()
{
	if (AttackCollision == nullptr)
	{
		return;
	}

	IsAttack = false;

	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UBoss1AnimInstance* ASlowMobCharacterBase::GetBossAnimInstance()
{
	UBoss1AnimInstance *BossAnimInstance = Cast<UBoss1AnimInstance>(GetAnimInstance());

	if (BossAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::GetBossAnimInstance :: Fail to Cast UBoss1AnimInstance."));
		return nullptr;
	}

	return BossAnimInstance;
}

UAnimMontage* ASlowMobCharacterBase::GetAttackMontage(int FindNum)
{
	if (!AttackMontages.IsValidIndex(FindNum))
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::GetAttackMontage :: No Found index[%d]."),FindNum);
		return nullptr;
	}
	
	return AttackMontages[FindNum];
}

bool ASlowMobCharacterBase::PlayMontage(UAnimMontage* montage)
{
	if (GetMesh()->GetAnimInstance()->Montage_Play(montage) == 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::PlayMontage :: Fail to Play Montage"));
		return false;
	}

	return true;
}

void ASlowMobCharacterBase::OnHitCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlowStatBasedCharacter* OtherCharacter = Cast<ASlowStatBasedCharacter>(OtherActor);

	if (OtherCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SlowAttackCollisionBeginOverlap :: Error(OtherCharacter == Nullptr)"));

		return;
	}
		

	if (OtherActor == this)
	{
		UE_LOG(LogTemp, Warning, TEXT("SlowAttackCollisionBeginOverlap :: Error(OtherActor == this)"));
		return;
	}
		

	if (IsAttack == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("SlowAttackCollisionBeginOverlap :: Error(IsAttack == false)"));
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}

	//AttackCollision->AddRelativeLocation(FVector(0.001f,0,0));

	DamageEffect->Apply(OtherCharacter);
	IsAttack = false;

	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Warning, TEXT("SlowAttackCollisionBeginOverlap :: character : %s"), *OtherActor->GetName());
}

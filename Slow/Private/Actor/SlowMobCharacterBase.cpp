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
	
	
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*AttackCollision->RegisterComponent();
	AddInstanceComponent(AttackCollision);*/

	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_FourWayAttack.MTG_Boss1_FourWayAttack'")).Object);
	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_ComboAttack.MTG_Boss1_ComboAttack'")).Object);
	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_spinningAttack.MTG_Boss1_SpinningAttack'")).Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FaintAnim(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_Faint.MTG_Boss1_Faint'"));
	FaintMontage = FaintAnim.Object;
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

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ASlowMobCharacterBase::OnHitCollisionBeginOverlap);
	DeltaHP = GetCurrentHP();
	CumDamageTime = 0.0f;
}

void ASlowMobCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (BehaviorCoolDown > 0.0f)
	{
		BehaviorCoolDown -= deltaTime;
	}
	
	else if(IsDead)
	{
		Destroy();
	}

	if (CumDamageTime >= 5.0f)
	{
		CumDamageTime = 0;
		DeltaHP = GetCurrentHP();
	}

	else
	{
		if (DeltaHP - GetCurrentHP() >= GetMaxHP() * 0.16f)
		{
			AddFaint(2.0f);
			CumDamageTime = 0;
			DeltaHP = GetCurrentHP();
		}
	}
}

bool ASlowMobCharacterBase::Monster_Attack()
{
	if (AttackCollision == nullptr)
	{
		return false;
	}

	IsAttack = true;
	//UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::Monster_Attack :: Monster Attack Init!"));
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

	//UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::Monster_AttackEnd :: Monster Attack End..."));
	//UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::Monster_AttackEnd :: Monster Attack End..."));
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

bool ASlowMobCharacterBase::GetIsDead() const
{
	return IsDead;
}

float ASlowMobCharacterBase::GetBehaviorCoolDown() const
{
	return BehaviorCoolDown;
}

void ASlowMobCharacterBase::OnActorKill()
{
	GetMesh()->GetAnimInstance()->StopAllMontages(0.01f);
	BehaviorCoolDown = 3.0f;
	IsDead = true;
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
	OtherCharacter->AddFaint(0.3f);
	IsAttack = false;

	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

bool ASlowMobCharacterBase::AddFaint(float num)
{
	if (num <= 0.0f)
	{
		return false;
	}

	if (IsDead)
	{
		return false;
	}

	if (BehaviorCoolDown < num)
		BehaviorCoolDown = num;

	GetMesh()->GetAnimInstance()->StopAllMontages(0.01f);
	PlayMontage(FaintMontage);

	return true;
}

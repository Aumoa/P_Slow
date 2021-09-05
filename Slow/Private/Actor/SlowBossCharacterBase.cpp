#include "Actor/SlowBossCharacterBase.h"
#include "Controller/SlowMobController.h"
#include "Effect/StatModifyLinearEffect.h"

ASlowBossCharacterBase::ASlowBossCharacterBase()
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
	AttackMontages.Emplace(ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_SpinningAttack.MTG_Boss1_SpinningAttack'")).Object);

	//AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_FourWayAttack.MTG_Boss1_FourWayAttack'

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FaintAnim(TEXT("AnimMontage'/Game/Slow/SkeletalMeshes/Boss1/MTG_Boss1_Faint.MTG_Boss1_Faint'"));
	FaintMontage = FaintAnim.Object;

	static ConstructorHelpers::FClassFinder<UCameraShake> CS_LoadCoustom(TEXT("/Game/Slow/Blueprints/Components/BP_BossAttackCameraShake"));
	if (CS_LoadCoustom.Succeeded())
	{
		CS_BossAttack = CS_LoadCoustom.Class;
	}

}

void ASlowBossCharacterBase::BeginPlay()
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

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ASlowBossCharacterBase::OnHitCollisionBeginOverlap);
	DeltaHP = GetCurrentHP();
	CumDamageTime = 0.0f;
}

void ASlowBossCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (BehaviorCoolDown > 0.0f)
	{
		BehaviorCoolDown -= deltaTime;
	}

	else if (IsDead)
	{
		Destroy();
	}

	else if (IsFaint)
	{
		CumDamageTime = 0;
		DeltaHP = GetCurrentHP();
		IsFaint = false;
	}

	if (CumDamageTime >= 5.0f)
	{
		CumDamageTime = 0;
		DeltaHP = GetCurrentHP();
	}

	else
	{
		if (!IsFaint && DeltaHP - GetCurrentHP() >= GetMaxHP() * GetInitialAttribute().FaintPercent)
		{
			AddFaint(6.f);
		}

		else
		{
			CumDamageTime += deltaTime;
		}
	}
}

bool ASlowBossCharacterBase::Monster_Attack()
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

void ASlowBossCharacterBase::Monster_AttackEnd()
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

UBoss1AnimInstance* ASlowBossCharacterBase::GetBossAnimInstance()
{
	UBoss1AnimInstance* BossAnimInstance = Cast<UBoss1AnimInstance>(GetAnimInstance());

	if (BossAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::GetBossAnimInstance :: Fail to Cast UBoss1AnimInstance."));
		return nullptr;
	}

	return BossAnimInstance;
}

UAnimMontage* ASlowBossCharacterBase::GetAttackMontage(int FindNum)
{
	if (!AttackMontages.IsValidIndex(FindNum))
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::GetAttackMontage :: No Found index[%d]."), FindNum);
		return nullptr;
	}

	return AttackMontages[FindNum];
}

bool ASlowBossCharacterBase::GetIsDead() const
{
	return IsDead;
}

float ASlowBossCharacterBase::GetBehaviorCoolDown() const
{
	return BehaviorCoolDown;
}

void ASlowBossCharacterBase::OnActorKill()
{
	GetMesh()->GetAnimInstance()->StopAllMontages(0.01f);
	BehaviorCoolDown = 3.0f;
	IsDead = true;
}

float ASlowBossCharacterBase::GetFaintHP()
{
	if (BehaviorCoolDown > 0.0f)
	{
		return GetInitialAttribute().MaxHealth;
	}

	return DeltaHP;
}

bool ASlowBossCharacterBase::PlayMontage(UAnimMontage* montage)
{
	if (GetMesh()->GetAnimInstance()->Montage_Play(montage) == 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASlowMobCharacterBase::PlayMontage :: Fail to Play Montage"));
		return false;
	}

	return true;
}



void ASlowBossCharacterBase::OnHitCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

	//DamageEffect->Apply(OtherCharacter);
	OtherCharacter->AddFaint(0.3f);
	IsAttack = false;

	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CS_BossAttack, 1.0f);
}

bool ASlowBossCharacterBase::AddFaint(float num)
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
	IsFaint = true;

	return true;
}
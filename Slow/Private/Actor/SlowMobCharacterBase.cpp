// Copyright 2020 Team slow. All right reserved.

#include "Actor/SlowMobCharacterBase.h"
#include "Controller/SlowMobController.h"
#include "Effect/StatModifyLinearEffect.h"

ASlowMobCharacterBase::ASlowMobCharacterBase()
{
	AIControllerClass = ASlowMobController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Collision_Attack = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_Attack"));
	Collision_Attack->SetupAttachment(RootComponent);
	Collision_Attack->OnComponentBeginOverlap.AddDynamic(this, &ASlowMobCharacterBase::OnHitCollisionBeginOverlap);
	Collision_Attack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void ASlowMobCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	DamageEffect = new FStatModifyLinearEffect(this);
	FAttrInstance DamageEffectAttr;
	DamageEffectAttr.HealthPoint = InitialAttribute.DefaultDamage;
	DamageEffect->SetModifyValue(DamageEffectAttr);
}

void ASlowMobCharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (IsAttack)
	{
		DeltaAttackDelay += deltaTime;


		if (DeltaAttackDelay >= MaxAttackDelay && DeltaAttackDelay < MaxAttackDelay + 0.2f)
		{
			Collision_Attack->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			
			
		}

		else if (DeltaAttackDelay >= MaxAttackDelay + 0.2f)
		{
			Collision_Attack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			IsAttack = false;
			DeltaAttackDelay = 0.0f;
		}
	}
}

bool ASlowMobCharacterBase::Attack()
{
	if (Collision_Attack == nullptr)
	{
		return false;
	}

	IsAttack = true;
	DrawDebugBox(GetWorld(), Collision_Attack->GetComponentLocation(), Collision_Attack->GetScaledBoxExtent(), 
		Collision_Attack->GetComponentRotation().Quaternion(),FColor::Yellow, false, 2.5f, 0, 5);
	return true;
}

void ASlowMobCharacterBase::OnHitCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlowStatBasedCharacter* OtherCharacter = Cast<ASlowStatBasedCharacter>(OtherActor);

	if (OtherCharacter == nullptr)
		return;

	if (OtherActor == this)
		return;

	if (IsAttack == false)
	{
		Collision_Attack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
		

	DamageEffect->Apply(OtherCharacter);
	IsAttack = false;

	UE_LOG(LogTemp, Warning, TEXT("SlowAttackCollisionBeginOverlap :: character : %s"), *OtherActor->GetName());


	
}

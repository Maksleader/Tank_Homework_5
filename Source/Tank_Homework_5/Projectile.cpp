// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "BaseCannon.h"
#include "Math/Vector.h"
#include "DamageTaker.h"
#include "TankPawn.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	
	
	
	

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	

	
}

void AProjectile::StartMove()
{
	ProjectileLocation = GetActorLocation();
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, Rate, true,Rate);
}




void AProjectile::Move()
{
	
	FVector Move = GetActorLocation()+GetActorForwardVector() * Rate * Speed;
	
	SetActorLocation(Move);

	if (FVector::Distance(ProjectileLocation,Move) > FlyRange)
	{
		Destroy();
	}
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	auto enemy = Cast<ABasePawn>(OtherActor);
	auto Target = Cast<IDamageTaker>(OtherActor);

	
	if(Target)
	{
		FDAMAGEDATA DamageData;
		DamageData.DamageValue = Damage;
		DamageData.Point = enemy->HealthComponent->GetDeathPoint();
		DamageData.DamageMaker = GetInstigator();
		DamageData.DamageTaker = enemy;
		DamageData.Instigator = this;
		Target->TakeDamage(DamageData);
		auto otheractor = Cast<IIScorable>(DamageData.DamageMaker);
		if(otheractor)
		{
			otheractor->AddScore(DamageData);
		}
		
	}

	else
	{
		OtherActor->Destroy();
	}

	Destroy();
}





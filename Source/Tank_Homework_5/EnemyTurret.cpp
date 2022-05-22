// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "BaseCannon.h"
#include  "Projectile.h"


AEnemyTurret::AEnemyTurret()
{
	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	RootComponent = Collision;

	Body->SetupAttachment(RootComponent);

	RangeSphere = CreateDefaultSubobject<USphereComponent>("RangeSphere");
	RangeSphere->SetupAttachment(RootComponent);

	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyTurret::OnBeginOverlap);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyTurret::OnEndOverlap);


	

}





void AEnemyTurret::OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                                  UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	OtherActor.Add(Actor);
	if (!Target.IsValid())
	{
		FindNextTarget();
	}
	
}


void AEnemyTurret::OnEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I)
{
	OtherActor.Remove(Actor);

	if(Actor==Target)
	{
		FindNextTarget();
	}
}

void AEnemyTurret::Destroyed()
{
	Super::Destroyed();

	if(Cannon)
	{
		Cannon->Destroy();
	}
}

void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AEnemyTurret::Targeting, TargetingRate, true);
}

void AEnemyTurret::Targeting()
{
	if(!Target.IsValid())
	{
		return;
	}


	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	Turret->SetWorldRotation(FMath::Lerp(Turret->GetComponentRotation(), TargetRotation, TargetingSpeed));

	auto TargetingDirection = Turret->GetForwardVector();
	auto PlayerDirection = Target->GetActorLocation() - GetActorLocation();
	PlayerDirection.Normalize();
	float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(TargetingDirection, PlayerDirection)));

	if(Angle<AimSlcak)
	{
		Fire();
	}
}



void AEnemyTurret::FindNextTarget()
{
	float MinRange = 100000;
	Target = nullptr;
	for (auto Actor : OtherActor)
	{
		float Range = FVector::Distance(Actor->GetActorLocation(), GetActorLocation());

		if(Range<MinRange)
		{
			MinRange = Range;
			Target = Actor;
		}
	}
}

void AEnemyTurret::OnDeath()
{
	Super::OnDeath();


	Destroy();
}

void AEnemyTurret::OnHealthChanged(float CurrentHealth)
{
	Super::OnHealthChanged(CurrentHealth);
	GEngine->AddOnScreenDebugMessage(5676, 10, FColor::Blue, FString::Printf(TEXT("Health:%f"), CurrentHealth));
}



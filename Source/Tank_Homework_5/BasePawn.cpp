// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "BaseCannon.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	


	Turret = CreateDefaultSubobject<UStaticMeshComponent>("Turret");
	Turret->SetupAttachment(Body);

	CannonSetup = CreateDefaultSubobject<UArrowComponent>("CannonSetup");
	CannonSetup->SetupAttachment(Turret);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ABasePawn::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ABasePawn::OnHealthChanged);
	HealthComponent->Killed.AddUObject(this, &ABasePawn::GetScore);


}

void ABasePawn::Fire()
{
	if(Cannon)
	Cannon->Fire();

}

void ABasePawn::SetUpCannon(TSubclassOf<ABaseCannon>& CannonType)
{

	if(Cannon)
	{
		Cannon->Destroy();
	}

	if(CannonClass.Num()==0)
	{
		return;
	}
	 Index = CannonClass.Find(CannonType);
	auto weapon=CannonClass[Index];

	if (CannonType)
	{
		
		const auto Transform = CannonSetup->GetComponentTransform();
		Cannon = GetWorld()->SpawnActor<ABaseCannon>(weapon, Transform);
		Cannon->AttachToComponent(CannonSetup, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Cannon->SetInstigator(this);
	}
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	Weapon = CannonClass[0];
	SetUpCannon(Weapon);
	
	
}

void ABasePawn::TakeDamage(FDAMAGEDATA DamageData)
{
	if (HealthComponent)
		HealthComponent->Damage(DamageData);
}

void ABasePawn::AddScore(FDAMAGEDATA DamageData)
{
	if(HealthComponent)
		HealthComponent->AddScore(DamageData);
}


// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::OnDeath()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Connect HealthComponent")));

}

void ABasePawn::OnHealthChanged(float CurrentHealth)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT(" HealthComponent")));
}

void ABasePawn::GetScore(float Score)
{
	GEngine->AddOnScreenDebugMessage(5676, 10, FColor::Red, FString::Printf(TEXT("Score:%f"), Score));
}




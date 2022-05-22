// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCannon.h"

// Sets default values
ABaseCannon::ABaseCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ABaseCannon::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Choose Weapon")));
}

void ABaseCannon::Reload()
{
	CurrentAmmo = Ammo;
}

void ABaseCannon::AddAmmo(float& Ammunition)
{
	CurrentAmmo = +Ammunition;
}

void ABaseCannon::BIsReadyToFire()
{
	bReadyToFire = true;
}

// Called when the game starts or when spawned
void ABaseCannon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = Ammo;
}

// Called every frame
void ABaseCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




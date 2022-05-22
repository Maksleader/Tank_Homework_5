// Fill out your copyright notice in the Description page of Project Settings.

#pragma optimize("", off)

#include "FireProjetile.h"
#include "Projectile.h"
#include "BasePawn.h"

void AFireProjetile:: Fire()
{

	
	if (!bReadyToFire)
		return;
	if (CurrentAmmo > 0)
	{
		
		
		Projectile=GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		Projectile->StartMove();
		Projectile->SetInstigator(this->GetInstigator());
		CurrentAmmo--;
		
	}
	bReadyToFire = false;
	
	GEngine->AddOnScreenDebugMessage(1237, 10, FColor::Green, FString::Printf(TEXT("%f/%f"),CurrentAmmo,Ammo));
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, FTimerDelegate::CreateUObject(this, &ABaseCannon::BIsReadyToFire), 1 /FireRate, false);
}

void AFireProjetile::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(1236, 10, FColor::Green, FString::Printf(TEXT("Time= %f "), GetWorld()->GetTimerManager().GetTimerElapsed(ReloadTimer)));

	
}





void AFireProjetile::BeginPlay()
{
	Super::BeginPlay();

}



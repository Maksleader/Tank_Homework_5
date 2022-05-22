// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTrace.h"

#include "BasePawn.h"
#include "DamageTaker.h"

void AFireTrace::Fire()
{
	
	if (!bReadyToFire)
		return;
	if (CurrentAmmo > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Use FirTrace")));
		FHitResult Result;
		FCollisionObjectQueryParams TraceParams;//= FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		TraceParams.AddObjectTypesToQuery(ECC_WorldStatic);
		TraceParams.AddObjectTypesToQuery(ECC_Visibility);
		
		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
		bool HasHit = GetWorld()->LineTraceSingleByObjectType(Result, start, end,TraceParams );
		if (HasHit)
		{
			end = Result.Location;
			if (Result.Actor.IsValid())
			{
				auto Target = Cast<IDamageTaker>(Result.Actor);
				auto enemy = Cast<ABasePawn>(Result.Actor);
				if (Target)
				{
					FDAMAGEDATA DamageData;
					DamageData.DamageMaker = GetInstigator();
					DamageData.DamageValue = FireDamage;
					DamageData.Instigator = this;
					DamageData.DamageTaker = Result.GetActor();
					DamageData.Point = enemy->HealthComponent->GetDeathPoint();
					Target->TakeDamage(DamageData);
					auto otheractor = Cast<IIScorable>(DamageData.DamageMaker);

					if(otheractor)
					{
						otheractor->AddScore(DamageData);
					}
				}

				else
				{
					Result.Actor->Destroy();
				}
			}
		}
		
		Reload();
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);

		CurrentAmmo--;
	}

	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, FTimerDelegate::CreateUObject(this, &ABaseCannon::BIsReadyToFire), 1 / FireRate, false);

	GEngine->AddOnScreenDebugMessage(1237, 10, FColor::Green, FString::Printf(TEXT("%f/%f"), CurrentAmmo, Ammo));
	
}

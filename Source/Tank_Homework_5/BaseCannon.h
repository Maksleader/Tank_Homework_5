// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BaseCannon.generated.h"

class AProjectile;
UCLASS()
class TANK_HOMEWORK_5_API ABaseCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCannon();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component")
	UArrowComponent* ProjectileSpawnPoint;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float FireDamage = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float Ammo = 5;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	TSubclassOf<AProjectile>ProjectileClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
	float CurrentAmmo = 5.0;


	
	virtual void  Fire();
	void Reload();
	void AddAmmo(float& Ammunition);
	void BIsReadyToFire();
	bool bReadyToFire = true;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ReloadTimer;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "GameFramework/Pawn.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "IScorable.h"
#include "BasePawn.generated.h"

class ABaseCannon;
UCLASS()
class TANK_HOMEWORK_5_API ABasePawn : public APawn,public IDamageTaker,public IIScorable
{
	GENERATED_BODY()

public:
	
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UStaticMeshComponent *Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent *Turret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetup;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret/Cannon")
	TArray<TSubclassOf<ABaseCannon>>CannonClass;

	TSubclassOf<ABaseCannon>Weapon;

	UPROPERTY()
	ABaseCannon* Cannon;





	void Fire();
	void SetUpCannon(TSubclassOf<ABaseCannon>& CannonType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 Index = 0;
	UFUNCTION()
	virtual void TakeDamage(FDAMAGEDATA DamageData) override;
	UFUNCTION()
	virtual void AddScore(FDAMAGEDATA DamageData) override;
	UFUNCTION()
	virtual  void OnDeath();

	UFUNCTION()
	virtual  void OnHealthChanged(float CurrentHealth);

	UFUNCTION()
	void GetScore(float Score);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	

};

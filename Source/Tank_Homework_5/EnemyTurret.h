// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "BasePawn.h"
#include  "Components/CapsuleComponent.h"
#include  "Components/SphereComponent.h"
#include "EnemyTurret.generated.h"

/**
 * 
 */
class AProjectile;
class ATankPawn;
UCLASS()
class TANK_HOMEWORK_5_API AEnemyTurret : public ABasePawn//,public IDamageTaker
{
	GENERATED_BODY()
public:
	
		AEnemyTurret();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* RangeSphere;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float AimSlcak = 5;


	

protected:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I);

	virtual void Destroyed() override;

	virtual void BeginPlay() override;

	void Targeting();

	

private:
	UPROPERTY()
	TArray<AActor*>OtherActor;

	TWeakObjectPtr<AActor>Target;

	void FindNextTarget();

	virtual void OnDeath() override;
	virtual void OnHealthChanged(float CurrentHealth) override;
};

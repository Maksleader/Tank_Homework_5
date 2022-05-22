// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "BaseCannon.h"
#include "FireProjetile.generated.h"
class AProjectile;
class ATankPawn;
class ABasePawn;
class ATank_Player_Controller;
/**
 * 
 */
UCLASS()
class TANK_HOMEWORK_5_API AFireProjetile : public ABaseCannon
{
	GENERATED_BODY()

public:
	
	virtual void Fire() override;

	virtual void Tick(float DeltaTime) override;

	
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	AProjectile*Projectile ;

	UPROPERTY()
		ABasePawn* Pawn;

};

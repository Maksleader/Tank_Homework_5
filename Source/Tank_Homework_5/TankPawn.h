// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "TankPawn.generated.h"

/**
 * 
 */
class ATank_Player_Controller;
class AProjectile;
UCLASS()
class TANK_HOMEWORK_5_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	
	ATankPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float ForwardInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float RotateInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float MoveSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float RotateSpeed = 100;

	UPROPERTY()
	float Point = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float RotationInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float TurretRotationInterpolationKey = 0.5f;
	

	


	virtual void Tick(float DeltaTime) override;


	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void WeaponSwitch();
	virtual void Destroyed() override;
	




protected:
	// Called when the game starts or whe
	virtual void BeginPlay() override;
private:
	void Move(float DeltaTime);
	void Rotate(float DeltaTime);	
	void CannonRotation(float DeltaTime) const;

	float MoveForwardScale = 0;
	float CurrentForwardScale = 0;
	float RotateScale = 0;
	float CurrentRotateScale = 0;
	
	
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float CurrentHealth) override;


	UPROPERTY()
	ATank_Player_Controller* TankController;

	



	
};

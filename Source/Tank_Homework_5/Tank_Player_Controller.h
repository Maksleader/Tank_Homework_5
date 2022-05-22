// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank_Player_Controller.generated.h"

/**
 * 
 */
class ATankPawn;
UCLASS()
class TANK_HOMEWORK_5_API ATank_Player_Controller : public APlayerController
{
	GENERATED_BODY()
public:
	ATank_Player_Controller();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	FVector GetMouseLocation()
	{
		return MouseLocation;
	}

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void Fire();
	void WeaponSwitch();
	UPROPERTY()
	FVector MouseLocation;

private:

	UPROPERTY()
	ATankPawn* Tank;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank_Player_Controller.h"
#include "TankPawn.h"

ATank_Player_Controller::ATank_Player_Controller()
{

}

void ATank_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATank_Player_Controller::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATank_Player_Controller::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATank_Player_Controller::Fire);
	InputComponent->BindAction("WeaponSwitch", IE_Pressed, this, &ATank_Player_Controller::WeaponSwitch);
	bShowMouseCursor = true;
}

void ATank_Player_Controller::Tick(float DeltaTime)
{
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	auto Z = FMath::Abs(Tank->GetActorLocation().Z - MouseLocation.Z);
	MouseLocation = MouseLocation - MouseDirection * Z / MouseDirection.Z;

}

void ATank_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATankPawn>(GetPawn());
	SetInstigator(GetPawn());
}

void ATank_Player_Controller::MoveForward(float Scale)
{
	if (Tank)
	{
		Tank->MoveForward(Scale);
	}
}

void ATank_Player_Controller::RotateRight(float Scale)
{
	if (Tank)
	{
		Tank->RotateRight(Scale);
	}
}

void ATank_Player_Controller::Fire()
{
	if (Tank)
	{
		Tank->Fire();
	}
}

void ATank_Player_Controller::WeaponSwitch()
{
	if(Tank)
	{
		Tank->WeaponSwitch();
	}
}

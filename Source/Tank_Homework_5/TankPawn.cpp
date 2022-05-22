// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Tank_Player_Controller.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "BaseCannon.h"
#include "Kismet/KismetSystemLibrary.h"

ATankPawn::ATankPawn()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
	Body->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	


	
	
}


void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Rotate(DeltaTime);	
	CannonRotation(DeltaTime);
}

void ATankPawn::MoveForward(float Scale)
{
	MoveForwardScale = Scale;
}

void ATankPawn::RotateRight(float Scale)
{
	RotateScale = Scale;
}

void ATankPawn::WeaponSwitch()
{
	++Index;
	if(Index==CannonClass.Num())
	{
		Index = 0;
	}
	Weapon = CannonClass[Index];
	SetUpCannon(Weapon);
}

void ATankPawn::Destroyed()
{
	Super::Destroyed();

	if(Cannon)
	{
		Cannon->Destroy();
	}
}






void ATankPawn::BeginPlay()
{
	
	Super::BeginPlay();
	TankController = Cast<ATank_Player_Controller>(GetController());
	
}

void ATankPawn::Move(float DeltaTime)
{
	CurrentForwardScale = FMath::Lerp(CurrentForwardScale, MoveForwardScale, ForwardInterpolationKey);
	const FVector CurrentLocation = GetActorLocation();
	const FVector ForwardVector = GetActorForwardVector();
	const FVector NewPosition = CurrentLocation + ForwardVector * MoveSpeed * CurrentForwardScale * DeltaTime;
	SetActorLocation(NewPosition, false);
	
}

void ATankPawn::Rotate(float DeltaTime)
{
	CurrentRotateScale = FMath::Lerp(CurrentRotateScale, RotateScale, RotateInterpolationKey);
	float YawRotation = CurrentRotateScale * RotateSpeed * DeltaTime;
	const FRotator CurrentRotation = GetActorRotation();
	YawRotation = CurrentRotation.Yaw + YawRotation;
	const FRotator NewRotation = FRotator(0, YawRotation, 0);
	SetActorRotation(NewRotation);
}

void ATankPawn::CannonRotation(float DeltaTime) const
{

	if (!TankController)
		return;

	FRotator OldRotation = Turret->GetComponentRotation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(Turret->GetComponentLocation(), TankController->GetMouseLocation());

	OldRotation.Yaw = TurretRotation.Yaw;
	TurretRotation.Pitch = OldRotation.Pitch;
	TurretRotation.Roll = OldRotation.Roll;

	Turret->SetWorldRotation(FMath::Lerp(OldRotation, TurretRotation, TurretRotationInterpolationKey));

	

}

void ATankPawn::OnDeath()
{
	Super::OnDeath();
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void ATankPawn::OnHealthChanged(float CurrentHealth)
{
	Super::OnHealthChanged(CurrentHealth);
	GEngine->AddOnScreenDebugMessage(5676, 10, FColor::Red, FString::Printf(TEXT("Health:%f"), CurrentHealth));
}




